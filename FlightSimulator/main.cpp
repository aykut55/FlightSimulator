#include <iostream>
#include <thread>
#include <mutex>

#include "src/SimEngine/SimEngine.h"
#include "src/SimEngineRunner/SimEngineRunner.h"

// ------------------------------------------------------------
// ScenarioPlayer: iterCount'a göre state geçişlerini dener
// ------------------------------------------------------------
class ScenarioPlayer
{
public:
    explicit ScenarioPlayer(CSimEngineRunner* runner)
        : m_runner(runner)
        , m_iter(0)
    {
    }

    int Run(int maxIterations = 40, int sleepMs = 500)
    {
        if (!m_runner)
            return -1;

        m_iter = 0;

        while (m_iter < maxIterations)
        {
            StepByIter(m_iter);

            std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
            ++m_iter;
        }

        return 0;
    }

private:
    // Basit state print (senin IsX fonksiyonlarını kullanır)
    void PrintState(const char* tag)
    {
        std::cout << "\n[" << tag << "] "
            << "Reset=" << m_runner->IsReset()
            << " Init=" << m_runner->IsInitialized()
            << " Started=" << m_runner->IsStarted()
            << " Running=" << m_runner->IsRunning()
            << " Paused=" << m_runner->IsPaused()
            << " Suspended=" << m_runner->IsSuspended()
            << " Freezed=" << m_runner->IsFreezed()
            << " Stopped=" << m_runner->IsStopped()
            << " Terminated=" << m_runner->IsTerminated()
            << std::endl;
    }

    void StepByIter(int i)
    {
        // Her adım öncesi state göster
        PrintState(("iter=" + std::to_string(i)).c_str());

        // --------------------------------------------------------
        // 1) İlk kurulum: Reset -> Init -> Start
        // --------------------------------------------------------
        if (i == 0) { std::cout << "Action: Reset\n";     m_runner->Reset();     return; }
        if (i == 1) { std::cout << "Action: Init\n";      m_runner->Init();      return; }
        if (i == 2) { std::cout << "Action: Start\n";     m_runner->Start();     return; }

        // --------------------------------------------------------
        // 2) Runtime kontrol testleri (Pause/Resume/Suspend/Freeze)
        // --------------------------------------------------------
        if (i == 5) { std::cout << "Action: Pause\n";     m_runner->Pause();     return; }
        if (i == 6) { std::cout << "Action: Resume\n";    m_runner->Resume();    return; }

        if (i == 8) { std::cout << "Action: Suspend\n";   m_runner->Suspend();   return; }
        if (i == 9) { std::cout << "Action: Resume\n";    m_runner->Resume();    return; }

        if (i == 11) { std::cout << "Action: Freeze\n";    m_runner->Freeze();    return; }
        if (i == 12) { std::cout << "Action: Resume\n";    m_runner->Resume();    return; }

        // --------------------------------------------------------
        // 3) Stop testi: Running/Paused/Suspended/Freezed iken Stop
        // --------------------------------------------------------
        if (i == 15) { std::cout << "Action: Stop\n";      m_runner->Stop();      return; }

        // Stop sonrası Start tekrar (Reset/Init beklemeden) denemek istersen:
        if (i == 16) { std::cout << "Action: Start (after Stop)\n"; m_runner->Start(); return; }

        // --------------------------------------------------------
        // 4) Terminate testi
        // --------------------------------------------------------
        if (i == 20) { std::cout << "Action: Terminate\n"; m_runner->Terminate(); return; }

        // Terminate sonrası "Stop/Pause/Resume" hiçbir şey yapmamalı (ignore testi)
        if (i == 21) { std::cout << "Action: Stop (should be ignored)\n";   m_runner->Stop();   return; }
        if (i == 22) { std::cout << "Action: Pause (should be ignored)\n";  m_runner->Pause();  return; }
        if (i == 23) { std::cout << "Action: Resume (should be ignored)\n"; m_runner->Resume(); return; }
        if (i == 24) { std::cout << "Action: Start (should be ignored)\n";  m_runner->Start();  return; }

        // --------------------------------------------------------
        // 5) Terminate sonrası doğru akış: Reset -> Init -> Start
        // --------------------------------------------------------
        if (i == 25) { std::cout << "Action: Reset (after Terminate)\n"; m_runner->Reset(); return; }
        if (i == 26) { std::cout << "Action: Init (after Terminate)\n";  m_runner->Init();  return; }
        if (i == 27) { std::cout << "Action: Start (after Terminate)\n"; m_runner->Start(); return; }

        // --------------------------------------------------------
        // 6) Birkaç kez Terminate çağrısı (idempotent testi)
        // --------------------------------------------------------
        if (i == 30) { std::cout << "Action: Terminate again\n"; m_runner->Terminate(); return; }
        if (i == 31) { std::cout << "Action: Terminate again\n"; m_runner->Terminate(); return; }

        // --------------------------------------------------------
        // 7) En sonda düzgün kapat
        // --------------------------------------------------------
        if (i == 35) { std::cout << "Action: Stop\n";      m_runner->Stop();      return; }
        if (i == 36) { std::cout << "Action: Terminate\n"; m_runner->Terminate(); return; }

        // default: sadece izleme
        std::cout << "Action: (no-op)\n";
    }

private:
    CSimEngineRunner* m_runner;
    int m_iter;
};

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

// ----------------------------------------
// Beklenen durum türleri
// ----------------------------------------
enum class Expected
{
    NoCheck = 0,

    Idle,
    ResetDone,
    Initialized,
    Running,
    Paused,
    Suspended,
    Freezed,
    Stopped,
    Terminated
};

static const char* ExpectedToStr(Expected e)
{
    switch (e)
    {
    case Expected::NoCheck:     return "NoCheck";
    case Expected::Idle:        return "Idle";
    case Expected::ResetDone:   return "ResetDone";
    case Expected::Initialized: return "Initialized";
    case Expected::Running:     return "Running";
    case Expected::Paused:      return "Paused";
    case Expected::Suspended:   return "Suspended";
    case Expected::Freezed:     return "Freezed";
    case Expected::Stopped:     return "Stopped";
    case Expected::Terminated:  return "Terminated";
    default:                    return "Unknown";
    }
}

struct FailRecord
{
    int iter = 0;
    std::string action;
    Expected expected = Expected::NoCheck;
    std::string actual;
    std::string note;
};

// ----------------------------------------
// ScenarioVerifier: action + expected state kontrol
// ----------------------------------------
class ScenarioVerifier
{
public:
    explicit ScenarioVerifier(CSimEngineRunner* r)
        : m_runner(r)
    {
    }

    int Run(int maxIter = 40, int sleepMs = 300)
    {
        if (!m_runner) return -1;

        m_passCount = 0;
        m_failCount = 0;
        m_fails.clear();

        for (int i = 0; i < maxIter; ++i)
        {
            Step(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
        }

        PrintSummary();
        return 0;
    }

    const std::vector<FailRecord>& GetFails() const { return m_fails; }

private:
    // Gerçek state'i string olarak üret (IsX fonksiyonlarından)
    std::string GetActualStateString() const
    {
        // Öncelik sırası önemli: daha "spesifik" durumları önce kontrol et
        if (m_runner->IsTerminated())  return "Terminated";
        if (m_runner->IsStopped())     return "Stopped";
        if (m_runner->IsSuspended())   return "Suspended";
        if (m_runner->IsFreezed())     return "Freezed";
        if (m_runner->IsPaused())      return "Paused";
        if (m_runner->IsRunning())     return "Running";
        if (m_runner->IsInitialized()) return "Initialized";
        if (m_runner->IsReset())       return "ResetDone";
        if (m_runner->IsIdle())        return "Idle";

        return "Unknown";
    }

    bool Matches(Expected exp) const
    {
        switch (exp)
        {
        case Expected::NoCheck:     return true;
        case Expected::Idle:        return m_runner->IsIdle();
        case Expected::ResetDone:   return m_runner->IsReset();
        case Expected::Initialized: return m_runner->IsInitialized();
        case Expected::Running:     return m_runner->IsRunning();
        case Expected::Paused:      return m_runner->IsPaused();
        case Expected::Suspended:   return m_runner->IsSuspended();
        case Expected::Freezed:     return m_runner->IsFreezed();
        case Expected::Stopped:     return m_runner->IsStopped();
        case Expected::Terminated:  return m_runner->IsTerminated();
        default:                    return false;
        }
    }

    void RecordPass(int iter, const std::string& action, Expected expected)
    {
        ++m_passCount;
        std::cout << "[PASS] iter=" << iter
            << " action=" << action
            << " expected=" << ExpectedToStr(expected)
            << " actual=" << GetActualStateString()
            << "\n";
    }

    void RecordFail(int iter, const std::string& action, Expected expected, const std::string& note = "")
    {
        ++m_failCount;

        FailRecord fr;
        fr.iter = iter;
        fr.action = action;
        fr.expected = expected;
        fr.actual = GetActualStateString();
        fr.note = note;
        m_fails.push_back(fr);

        std::cout << "[FAIL] iter=" << iter
            << " action=" << action
            << " expected=" << ExpectedToStr(expected)
            << " actual=" << fr.actual;

        if (!note.empty())
            std::cout << " note=" << note;

        std::cout << "\n";
    }

    void DoAndCheck(int iter, const std::string& action, Expected expected, void (CSimEngineRunner::* fn)())
    {
        // çağır
        (m_runner->*fn)();

        // kontrol
        if (Matches(expected))
            RecordPass(iter, action, expected);
        else
            RecordFail(iter, action, expected);
    }

    // overload: int dönen methodlar için
    void DoAndCheckInt(int iter, const std::string& action, Expected expected, int (CSimEngineRunner::* fn)())
    {
        (m_runner->*fn)();

        if (Matches(expected))
            RecordPass(iter, action, expected);
        else
            RecordFail(iter, action, expected);
    }

    void Step(int i)
    {
        // ---- Senaryo Scripti ----
        // Terminate sonrası Stop/Pause/Resume hiçbir şey yapmayacak kuralını da test ediyoruz.

        switch (i)
        {
            // İlk başlatma: Reset->Init->Start
        case 0:  DoAndCheckInt(i, "Reset", Expected::ResetDone, &CSimEngineRunner::Reset);      break;
        case 1:  DoAndCheckInt(i, "Init", Expected::Initialized, &CSimEngineRunner::Init);       break;
        case 2:  DoAndCheckInt(i, "Start", Expected::Running, &CSimEngineRunner::Start);      break;

            // Pause/Resume testi
        case 5:  DoAndCheckInt(i, "Pause", Expected::Paused, &CSimEngineRunner::Pause);      break;
        case 6:  DoAndCheckInt(i, "Resume", Expected::Running, &CSimEngineRunner::Resume);     break;

            // Suspend/Resume testi
        case 8:  DoAndCheckInt(i, "Suspend", Expected::Suspended, &CSimEngineRunner::Suspend);    break;
        case 9:  DoAndCheckInt(i, "Resume", Expected::Running, &CSimEngineRunner::Resume);     break;

            // Freeze/Resume testi
        case 11: DoAndCheckInt(i, "Freeze", Expected::Freezed, &CSimEngineRunner::Freeze);     break;
        case 12: DoAndCheckInt(i, "Resume", Expected::Running, &CSimEngineRunner::Resume);     break;

            // Stop testi (Paused/Suspended/Freezed de olabilir; burada running iken çağırıyoruz)
        case 15: DoAndCheckInt(i, "Stop", Expected::Stopped, &CSimEngineRunner::Stop);       break;

            // Stop sonrası Start tekrar
        case 16: DoAndCheckInt(i, "Start(after Stop)", Expected::Running, &CSimEngineRunner::Start); break;

            // Terminate testi
        case 20: DoAndCheckInt(i, "Terminate", Expected::Terminated, &CSimEngineRunner::Terminate); break;

            // Terminated iken Stop/Pause/Resume ignore olmalı => state Terminated kalmalı
        case 21: DoAndCheckInt(i, "Stop(ignored)", Expected::Terminated, &CSimEngineRunner::Stop);   break;
        case 22: DoAndCheckInt(i, "Pause(ignored)", Expected::Terminated, &CSimEngineRunner::Pause);  break;
        case 23: DoAndCheckInt(i, "Resume(ignored)", Expected::Terminated, &CSimEngineRunner::Resume); break;

            // Terminate sonrası doğru akış: Reset->Init->Start
        case 25: DoAndCheckInt(i, "Reset(after Terminate)", Expected::ResetDone, &CSimEngineRunner::Reset);  break;
        case 26: DoAndCheckInt(i, "Init(after Terminate)", Expected::Initialized, &CSimEngineRunner::Init);   break;
        case 27: DoAndCheckInt(i, "Start(after Terminate)", Expected::Running, &CSimEngineRunner::Start);  break;

            // Terminate idempotent testi
        case 30: DoAndCheckInt(i, "Terminate again", Expected::Terminated, &CSimEngineRunner::Terminate); break;
        case 31: DoAndCheckInt(i, "Terminate again", Expected::Terminated, &CSimEngineRunner::Terminate); break;

        default:
            // kontrol yok, sadece bilgi
            std::cout << "[INFO] iter=" << i << " no action; actual=" << GetActualStateString() << "\n";
            break;
        }
    }

    void PrintSummary() const
    {
        std::cout << "\n==================== SUMMARY ====================\n";
        std::cout << "PASS=" << m_passCount << " FAIL=" << m_failCount << "\n";

        if (!m_fails.empty())
        {
            std::cout << "\n---- FAIL LIST ----\n";
            for (const auto& f : m_fails)
            {
                std::cout << "iter=" << f.iter
                    << " action=" << f.action
                    << " expected=" << ExpectedToStr(f.expected)
                    << " actual=" << f.actual;

                if (!f.note.empty())
                    std::cout << " note=" << f.note;

                std::cout << "\n";
            }
        }
        std::cout << "=================================================\n";
    }

private:
    CSimEngineRunner* m_runner = nullptr;
    int m_passCount = 0;
    int m_failCount = 0;
    std::vector<FailRecord> m_fails;
};

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

// ------------------------------------------------------------
// TEST MATRIX: 모든 state x action kombinasyonlarını test eder
// ------------------------------------------------------------
class StateMatrixTester
{
public:
    enum class S
    {
        Unknown = 0,
        //Idle,
        ResetDone,
        Initialized,
        Running,
        Paused,
        Suspended,
        Freezed,
        Stopped,
        Terminated
    };

    enum class A
    {
        Reset,
        Init,
        Start,
        Stop,
        Terminate,
        Pause,
        Suspend,
        Freeze,
        Resume
    };

    struct Fail
    {
        std::string fromState;
        std::string action;
        std::string expected;
        std::string actual;
        std::string note;
    };

public:
    explicit StateMatrixTester(CSimEngineRunner* r)
        : m(r)
    {
    }

    int RunAll(int timeoutMsPerStep = 2000)
    {
        if (!m) return -1;

        mFails.clear();
        int pass = 0, fail = 0;

        const S states[] = {
            //S::Idle, 
            S::ResetDone, S::Initialized, S::Running, S::Paused, S::Suspended, S::Freezed, S::Stopped, S::Terminated
        };

        const A actions[] = {
            A::Reset, A::Init, A::Start, A::Stop, A::Terminate, A::Pause, A::Suspend, A::Freeze, A::Resume
        };

        std::cout << "\n===== STATE MATRIX TEST START =====\n";

        for (S from : states)
        {
            for (A act : actions)
            {
                std::cout
                    << "\n----------------------------------------\n"
                    << "FROM STATE : " << ToStr(from) << "\n"
                    << "ACTION     : " << ToStr(act) << "\n"
                    << "----------------------------------------\n";


                // 1) Kaynak state'e zorla gir
                if (!EnsureState(from, timeoutMsPerStep))
                {
                    RecordFail(from, act, S::Unknown, GetState(), "EnsureState failed");
                    ++fail;
                    continue;
                }

                // 2) Beklenen state'i tabloya göre hesapla
                S expected = ExpectedNext(from, act);

                // 3) Aksiyonu uygula
                Apply(act);

                // 4) Beklenen state'e gelmesini bekle (bazı geçişler gecikebilir)
                if (expected == S::Unknown)
                {
                    // Unknown: kontrol etme (istersen fail de sayabilirsin)
                    std::cout << "[INFO] from=" << ToStr(from) << " action=" << ToStr(act)
                        << " expected=Unknown (no-check) actual=" << ToStr(GetState()) << "\n";
                    continue;
                }

                bool ok = WaitUntil(expected, timeoutMsPerStep);

                if (ok)
                {
                    ++pass;
                    std::cout << "[PASS] from=" << ToStr(from) << " action=" << ToStr(act)
                        << " => " << ToStr(expected) << "\n";
                }
                else
                {
                    ++fail;
                    RecordFail(from, act, expected, GetState(), "timeout / wrong transition");
                    std::cout << "[FAIL] from=" << ToStr(from) << " action=" << ToStr(act)
                        << " expected=" << ToStr(expected)
                        << " actual=" << ToStr(GetState()) << "\n";
                }
            }
        }

        std::cout << "\n===== SUMMARY =====\n";
        std::cout << "PASS=" << pass << " FAIL=" << fail << "\n";

        if (!mFails.empty())
        {
            std::cout << "\n---- FAIL LIST ----\n";
            for (const auto& f : mFails)
            {
                std::cout << "from=" << f.fromState
                    << " action=" << f.action
                    << " expected=" << f.expected
                    << " actual=" << f.actual;
                if (!f.note.empty()) std::cout << " note=" << f.note;
                std::cout << "\n";
            }
        }

        std::cout << "===== STATE MATRIX TEST END =====\n";
        return 0;
    }

private:
    // -----------------------------
    // State okuma (IsX fonksiyonlarından)
    // -----------------------------
    S GetState() const
    {
        // Öncelik önemli
        if (m->IsTerminated())  return S::Terminated;
        if (m->IsStopped())     return S::Stopped;
        if (m->IsSuspended())   return S::Suspended;
        if (m->IsFreezed())     return S::Freezed;
        if (m->IsPaused())      return S::Paused;
        if (m->IsRunning())     return S::Running;
        if (m->IsInitialized()) return S::Initialized;
        if (m->IsReset())       return S::ResetDone;
        //if (m->IsIdle())        return S::Idle;
        return S::Unknown;
    }

    bool WaitUntil(S expected, int timeoutMs) const
    {
        const int step = 50;
        int elapsed = 0;
        while (elapsed < timeoutMs)
        {
            if (GetState() == expected)
                return true;
            std::this_thread::sleep_for(std::chrono::milliseconds(step));
            elapsed += step;
        }
        return (GetState() == expected);
    }

    // -----------------------------
    // Action uygulama
    // -----------------------------
    void Apply(A a)
    {
        switch (a)
        {
        case A::Reset:     m->Reset();     break;
        case A::Init:      m->Init();      break;
        case A::Start:     m->Start();     break;
        case A::Stop:      m->Stop();      break;
        case A::Terminate: m->Terminate(); break;
        case A::Pause:     m->Pause();     break;
        case A::Suspend:   m->Suspend();   break;
        case A::Freeze:    m->Freeze();    break;
        case A::Resume:    m->Resume();    break;
        default: break;
        }
    }

    // -----------------------------
    // Allowed transitions tablosu (senin kuralların)
    // -----------------------------
    S ExpectedNext(S from, A a) const
    {
        // Terminated iken (Reset hariç) hiçbir şey yapma
        if (from == S::Terminated)
        {
            if (a == A::Reset)     return S::ResetDone;   // Terminate sonrası yeni döngü kapısı
            if (a == A::Terminate) return S::Terminated;  // idempotent
            return S::Terminated;                          // Stop/Pause/Resume/Start/Init/Suspend/Freeze ignore
        }

        // Reset: her yerden ResetDone'a geçebilir (sen "her zaman çağırabilir" demiştin)
        if (a == A::Reset) return S::ResetDone;

        // Init: sadece ResetDone -> Initialized, diğerlerinde ignore (state değişmez)
        if (a == A::Init)
        {
            return (from == S::ResetDone) ? S::Initialized : from;
        }

        // Start: sadece Initialized veya Stopped -> Running, diğerlerinde ignore
        if (a == A::Start)
        {
            return (from == S::Initialized || from == S::Stopped) ? S::Running : from;
        }

        // Stop: Running/Paused/Suspended/Freezed -> Stopped, diğerlerinde ignore
        if (a == A::Stop)
        {
            if (from == S::Running || from == S::Paused || from == S::Suspended || from == S::Freezed)
                return S::Stopped;
            return from;
        }

        // Terminate: her yerden Terminated (idempotent)
        if (a == A::Terminate) return S::Terminated;

        // Pause: sadece Running -> Paused, diğerlerinde ignore
        if (a == A::Pause)
        {
            return (from == S::Running) ? S::Paused : from;
        }

        // Suspend: Running/Paused -> Suspended, diğerlerinde ignore
        if (a == A::Suspend)
        {
            return (from == S::Running || from == S::Paused) ? S::Suspended : from;
        }

        // Freeze: Running/Paused -> Freezed, diğerlerinde ignore
        if (a == A::Freeze)
        {
            return (from == S::Running || from == S::Paused) ? S::Freezed : from;
        }

        // Resume: Paused/Suspended/Freezed -> Running, diğerlerinde ignore
        if (a == A::Resume)
        {
            return (from == S::Paused || from == S::Suspended || from == S::Freezed) ? S::Running : from;
        }

        return S::Unknown;
    }

    // -----------------------------
    // State'i oluşturma (kaynak state'e zorla gir)
    // -----------------------------
    bool EnsureState(S target, int timeoutMs)
    {
/*
        // Idle: sadece yeni oluşturulduğunda vardır. Burada "best effort":
        if (target == S::Idle)
        {
            // Eğer gerçekten Idle'da değilsek, bunu geri getirmek genelde mümkün değil.
            // Bu yüzden Idle testlerini genelde runner yaratılır yaratılmaz çalıştır.
            return (GetState() == S::Idle);
        }
*/
        // Terminated'e gitmek kolay:
        if (target == S::Terminated)
        {
            m->Terminate();
            return WaitUntil(S::Terminated, timeoutMs);
        }

        // ResetDone
        if (target == S::ResetDone)
        {
            m->Reset();
            return WaitUntil(S::ResetDone, timeoutMs);
        }

        // Initialized
        if (target == S::Initialized)
        {
            m->Reset();
            if (!WaitUntil(S::ResetDone, timeoutMs)) return false;
            m->Init();
            return WaitUntil(S::Initialized, timeoutMs);
        }

        // Running
        if (target == S::Running)
        {
            // Terminated ise zorla yeni döngü
            if (GetState() == S::Terminated)
            {
                m->Reset();
                if (!WaitUntil(S::ResetDone, timeoutMs)) return false;
                m->Init();
                if (!WaitUntil(S::Initialized, timeoutMs)) return false;
                m->Start();
                return WaitUntil(S::Running, timeoutMs);
            }

            // diğer durumlarda: güvenli yol Reset->Init->Start
            m->Reset();
            if (!WaitUntil(S::ResetDone, timeoutMs)) return false;
            m->Init();
            if (!WaitUntil(S::Initialized, timeoutMs)) return false;
            m->Start();
            return WaitUntil(S::Running, timeoutMs);
        }

        // Paused
        if (target == S::Paused)
        {
            if (!EnsureState(S::Running, timeoutMs)) return false;
            m->Pause();
            return WaitUntil(S::Paused, timeoutMs);
        }

        // Suspended
        if (target == S::Suspended)
        {
            if (!EnsureState(S::Running, timeoutMs)) return false;
            m->Suspend();
            return WaitUntil(S::Suspended, timeoutMs);
        }

        // Freezed
        if (target == S::Freezed)
        {
            if (!EnsureState(S::Running, timeoutMs)) return false;
            m->Freeze();
            return WaitUntil(S::Freezed, timeoutMs);
        }

        // Stopped
        if (target == S::Stopped)
        {
            if (!EnsureState(S::Running, timeoutMs)) return false;
            m->Stop();
            return WaitUntil(S::Stopped, timeoutMs);
        }

        return false;
    }

    // -----------------------------
    // Log helpers
    // -----------------------------
    void RecordFail(S from, A act, S expected, S actual, const std::string& note)
    {
        Fail f;
        f.fromState = ToStr(from);
        f.action = ToStr(act);
        f.expected = ToStr(expected);
        f.actual = ToStr(actual);
        f.note = note;
        mFails.push_back(f);
    }

    static const char* ToStr(S s)
    {
        switch (s)
        {
        //case S::Idle:        return "Idle";
        case S::ResetDone:   return "ResetDone";
        case S::Initialized: return "Initialized";
        case S::Running:     return "Running";
        case S::Paused:      return "Paused";
        case S::Suspended:   return "Suspended";
        case S::Freezed:     return "Freezed";
        case S::Stopped:     return "Stopped";
        case S::Terminated:  return "Terminated";
        default:             return "Unknown";
        }
    }

    static const char* ToStr(A a)
    {
        switch (a)
        {
        case A::Reset:     return "Reset";
        case A::Init:      return "Init";
        case A::Start:     return "Start";
        case A::Stop:      return "Stop";
        case A::Terminate: return "Terminate";
        case A::Pause:     return "Pause";
        case A::Suspend:   return "Suspend";
        case A::Freeze:    return "Freeze";
        case A::Resume:    return "Resume";
        default:           return "UnknownAction";
        }
    }

private:
    CSimEngineRunner* m = nullptr;
    std::vector<Fail> mFails;
};

int iterCout = 0;
int waitSimEngineRunnerTerminate(CSimEngineRunner* pSimEngineRunner)
{
    bool isRunning = true;

    if (pSimEngineRunner == nullptr)
        return -1;

    iterCout = 0;
    while (isRunning)
    {       
        isRunning = (pSimEngineRunner->IsStopped() || pSimEngineRunner->IsTerminated()) ? false : true;
        if (!isRunning)
            break;

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //std::cout << std::endl << "waitSimEngineRunnerTerminate..." << std::endl;

        iterCout++;

        if (iterCout == 100) {
            pSimEngineRunner->Suspend();
        }

        if (iterCout == 200) {
            pSimEngineRunner->Resume();
        }

        if (iterCout == 300) {
            pSimEngineRunner->Pause();
        }

        if (iterCout == 400) {
            pSimEngineRunner->Resume();
        }

        if (iterCout == 500) {
            pSimEngineRunner->Freeze();
        }

        if (iterCout == 600) {
            pSimEngineRunner->Resume();
        }

        if (iterCout == 700) {
            pSimEngineRunner->Stop();
        }
    }

    return 0;
}

int main()
{
    std::cout << std::endl;
    std::cout << "=== Aykut Flight Simulator ===" << std::endl;

    std::cout << std::endl;
    std::cout << "Initializing simulation engine..." << std::endl;

    std::cout << std::endl;

    CSimEngineRunner* pSimEngineRunner = new CSimEngineRunner();
    {
        pSimEngineRunner->Reset();

        // Setterler cagrilacak

        pSimEngineRunner->Init();

        pSimEngineRunner->Start();

        waitSimEngineRunnerTerminate(pSimEngineRunner);

        pSimEngineRunner->Stop();

        pSimEngineRunner->Terminate();
    }
    delete pSimEngineRunner;

/*
    CSimEngineRunner* pSimEngineRunner = new CSimEngineRunner();

    {
        StateMatrixTester tester(pSimEngineRunner);
        tester.RunAll(2000); // her adım için 2sn timeout

        ScenarioPlayer player(pSimEngineRunner);
        //player.Run(40, 500);

        ScenarioVerifier verifier(pSimEngineRunner);
        //verifier.Run(40, 300); // 40 iter, 300ms
    }

    delete pSimEngineRunner;
*/
/*
    SimEngine* simEngine = runner.getSimEngine();

    std::cout << "\n--- Test 1: Running for 100 steps ---" << std::endl;
    runner.runForSteps(100);

    simEngine->reset();

    std::cout << "\n--- Test 2: Running for 5.0 seconds of simulation time ---" << std::endl;
    runner.runForTime(5.0);

    std::cout << "\n--- Shutting down ---" << std::endl;
    simEngine->shutdown();

    std::cout << "\n=== Simulation Complete ===" << std::endl;
*/
    return 0;
}
