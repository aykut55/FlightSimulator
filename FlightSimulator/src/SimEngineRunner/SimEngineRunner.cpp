#include "SimEngineRunner.h"
#include <iostream>
#include <sstream>
#include <chrono>

CSimEngineRunner::~CSimEngineRunner()
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] Destructor called" << std::endl;
    }

    stopThreads();
}

CSimEngineRunner::CSimEngineRunner()
    : pSimEngine(nullptr)
    , shouldExit(false)
    , maxSteps(0)
    , maxSimTime(0.0)
    , m_state(EState::Idle)
    , m_simulationTimeMSec(0)
    , m_activeSimulationTimeMSec(0)
	, m_suspendedSimulationTimeMSec(0)
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] Constructor called" << std::endl;
    }
    pSimEngine = CSimEngine::getInstance();

    startThreads();
}

bool CSimEngineRunner::IsIdle(void)
{
    return (m_state.load() == EState::Idle);
}

bool CSimEngineRunner::IsReset(void)
{
    return (m_state.load() == EState::ResetDone);
}

bool CSimEngineRunner::IsInitialized(void)
{
    return (m_state.load() == EState::Initialized);
}

bool CSimEngineRunner::IsStarted(void)
{
    // Eski "isStarted" artık ayrı bir sayaç değil.
    // "Başladı" demek: En az bir kez Running/Paused/Suspended/Freezed/Stopped durumlarına girmiş olmak olabilir.
    // Şimdilik en pratik karşılık: Initialized'dan sonraki tüm aktif durumlar.
    const EState s = m_state.load();
    return (s == EState::Running ||
        s == EState::Paused ||
        s == EState::Suspended ||
        s == EState::Freezed ||
        s == EState::Stopped);
}

bool CSimEngineRunner::IsRunning(void)
{
    return (m_state.load() == EState::Running);
}

bool CSimEngineRunner::IsPaused(void)
{
    return (m_state.load() == EState::Paused);
}

bool CSimEngineRunner::IsSuspended(void)
{
    return (m_state.load() == EState::Suspended);
}

bool CSimEngineRunner::IsFreezed(void)
{
    return (m_state.load() == EState::Freezed);
}

bool CSimEngineRunner::IsResumed(void)
{
    // TODO: "Resumed" ayrı bir state değil; Resume() sonrası Running olur.
    // Eğer özellikle "Resume en son çağrıldı mı?" gibi bir şey istiyorsan ayrı bir flag / counter gerekir.
    return false;
}

bool CSimEngineRunner::IsStopped(void)
{
    return (m_state.load() == EState::Stopped);
}

bool CSimEngineRunner::IsTerminated(void)
{
    return (m_state.load() == EState::Terminated);
}

bool CSimEngineRunner::IsWaiting(void)
{
    // TODO: "Waiting" senin eski kurgunda neydi? (Idle thread bekliyor mu, CV wait mi, vs.)
    // Tek state modelinde bunun karşılığı ayrı bir alt-state olabilir.
    return false;
}

int CSimEngineRunner::Reset(void)
{
    std::lock_guard<std::mutex> g(m_stateMutex);

    {
        std::lock_guard<std::mutex> lock(coutMutex); 
        std::cout << std::endl << "[CSimEngineRunner] Reset called" << std::endl;
    }

    m_state.store(EState::ResetDone);

    if (pSimEngine != nullptr) {
        pSimEngine->reset();
    }

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Reset done" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::Init(void)
{
    std::lock_guard<std::mutex> g(m_stateMutex);

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Init called" << std::endl;
    }

    bool willBeDone = false;
    bool alreadyDone = false;

    const EState s = m_state.load();

    if (s == EState::ResetDone)
        willBeDone = true;
    else
        alreadyDone = true;

    if (willBeDone)
    {
        if (pSimEngine != nullptr)
            pSimEngine->initialize();

        m_state.store(EState::Initialized);

        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << std::endl << "[CSimEngineRunner] Init done" << std::endl;
        }
    }
    else if (alreadyDone)
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Init ignored (Reset not done or already initialized)"
            << std::endl;
    }

    return 0;
}

int CSimEngineRunner::Start(void)
{
    std::lock_guard<std::mutex> g(m_stateMutex);

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Start called" << std::endl;
    }

    if (IsTerminatedState())
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] Terminate ignored (already terminated)" << std::endl;
        return 0;
    }

    bool willBeDone = false;
    bool alreadyDone = false;

    const EState s = m_state.load();

    if (s == EState::Terminated)
    {
        alreadyDone = true;
    }
    else if (s == EState::Initialized)
    {
        willBeDone = true; // ilk start
    }
    else if (s == EState::Stopped)
    {
        willBeDone = true; // stop sonrası yeniden start
    }
    else
    {
        alreadyDone = true;
    }

    if (willBeDone)
    {
        // Stop sonrası threadler kapalıysa yeniden aç
        if (s == EState::Stopped)
            startThreads();

        if (pSimEngine != nullptr)
            pSimEngine->run();  // sende resume varsa burada daha doğru olur

        m_state.store(EState::Running);

        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << std::endl << "[CSimEngineRunner] Start done" << std::endl;
        }
    }
    else if (alreadyDone)
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Start ignored (wrong state or terminated)"
            << std::endl;
    }

    return 0;
}

int CSimEngineRunner::Stop(void)
{
    std::lock_guard<std::mutex> g(m_stateMutex);

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Stop called" << std::endl;
    }

    if (IsTerminatedState())
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] Terminate ignored (already terminated)" << std::endl;
        return 0;
    }

    bool willBeDone = false;
    bool alreadyDone = false;

    const EState s = m_state.load();

    if (s == EState::Running || s == EState::Paused || s == EState::Suspended || s == EState::Freezed)
        willBeDone = true;
    else
        alreadyDone = true;

    if (willBeDone)
    {
        if (pSimEngine != nullptr)
            pSimEngine->pause(); // senin stop mantığın böyleydi

        stopThreads();
        m_state.store(EState::Stopped);

        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << std::endl << "[CSimEngineRunner] Stop done" << std::endl;
        }
    }
    else if (alreadyDone)
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Stop ignored (not running/paused/suspended/freezed)"
            << std::endl;
    }

    return 0;
}

int CSimEngineRunner::Terminate(void)
{
    std::lock_guard<std::mutex> g(m_stateMutex);

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Terminate called" << std::endl;
    }

    bool willBeDone = false;
    bool alreadyDone = false;

    const EState s = m_state.load();

    if (s == EState::Terminated)
    {
        alreadyDone = true;
    }
    else
    {
        willBeDone = true;
    }

    if (willBeDone)
    {
        // 1) Engine shutdown sadece 1 kere
        try { 
            if (pSimEngine) 
                pSimEngine->shutdown(); 
        }
        catch (...) { /* log */ }

        // 2) Threadleri kapat (stopThreads zaten idempotent olmaya yakın; yine de güvenli)
        try { stopThreads(); }
        catch (...) { /* log */ }

        // 3) State'i Terminated yap
        m_state.store(EState::Terminated);

        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "[CSimEngineRunner] Terminate done" << std::endl;
        }
    }
    else if (alreadyDone)
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] Terminate ignored (already terminated)" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::Pause(void)
{
    std::lock_guard<std::mutex> g(m_stateMutex);

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Pause called" << std::endl;
    }

    if (IsTerminatedState())
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] Terminate ignored (already terminated)" << std::endl;
        return 0;
    }

    bool willBeDone = false;
    bool alreadyDone = false;

    if (m_state.load() == EState::Running)
        willBeDone = true;
    else
        alreadyDone = true;

    if (willBeDone)
    {
        if (pSimEngine != nullptr)
            pSimEngine->pause();

        m_state.store(EState::Paused);
    }
    else if (alreadyDone)
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Pause ignored (not running)" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::Suspend(void)
{
    std::lock_guard<std::mutex> g(m_stateMutex);

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Suspend called" << std::endl;
    }

    if (IsTerminatedState())
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] Terminate ignored (already terminated)" << std::endl;
        return 0;
    }

    const EState s = m_state.load();
    if (s == EState::Running || s == EState::Paused)
    {
        // suspendThreads(); ← Thread'leri suspend etme, sadece state değiştir
        m_state.store(EState::Suspended);
    }
    else
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Suspend ignored (wrong state)" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::Freeze(void)
{
    std::lock_guard<std::mutex> g(m_stateMutex);

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Freeze called" << std::endl;
    }

    if (IsTerminatedState())
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] Terminate ignored (already terminated)" << std::endl;
        return 0;
    }

    const EState s = m_state.load();
    if (s == EState::Running || s == EState::Paused)
    {
        // pSimEngine->freeze(); varsa
        m_state.store(EState::Freezed);
    }
    else
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Freeze ignored (wrong state)" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::Resume(void)
{
    std::lock_guard<std::mutex> g(m_stateMutex);

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Resume called" << std::endl;
    }

    if (IsTerminatedState())
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] Terminate ignored (already terminated)" << std::endl;
        return 0;
    }

    const EState s = m_state.load();

    if (s == EState::Paused)
    {
        if (pSimEngine != nullptr)
            pSimEngine->run(); // sende resume varsa onu çağır

        m_state.store(EState::Running);
        return 0;
    }

    if (s == EState::Suspended)
    {
        // resumeThreads(); ← Thread'ler zaten çalışıyor, sadece state değiştir
        if (pSimEngine != nullptr)
            pSimEngine->run();

        m_state.store(EState::Running);
        return 0;
    }

    if (s == EState::Freezed)
    {
        // pSimEngine->unfreeze(); varsa
        if (pSimEngine != nullptr)
            pSimEngine->run();

        m_state.store(EState::Running);
        return 0;
    }

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Resume ignored (wrong state)" << std::endl;
    }
    return 0;
}

int CSimEngineRunner::Update(void)
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] Update called" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::UpdateTime(void)
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] UpdateTime called" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::UpdateCounters(void)
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] UpdateCounters called" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::UpdateConfig(void)
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::endl << "[CSimEngineRunner] UpdateConfig called" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::timerThreadFunc(void)
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] timerThreadFunc() thread started" << std::endl;
    }

    while (!timerThreadParams.isExitRequested)
    {
        {
            std::unique_lock<std::mutex> lock(timerThreadParams.suspendMutex);
            timerThreadParams.suspendCV.wait(lock, [this] { return !timerThreadParams.isSuspended || timerThreadParams.isExitRequested; });

            if (timerThreadParams.isExitRequested)
                break;
        }

        // Update wall clock simulation time (always increments)
        {
            std::lock_guard<std::mutex> lock(m_timeMutex);
            m_simulationTimeMSec.fetch_add(1);

            if (IsRunning())
            {
                // Running durumunda activeTime artıyor (catch-up'ta)
            }
            else if (IsSuspended() || IsPaused() || IsFreezed())
            {
                //m_suspendedSimulationTimeMSec.fetch_add(1);
            }
            else
            {
				// Diğer durumlarda zaman artışı yok
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    timerThreadParams.isExited = true;
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] timerThreadFunc() thread exited" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::idleThreadFunc(void)
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] idleThreadFunc() thread started" << std::endl;
    }

    while (!idleThreadParams.isExitRequested)
    {
        {
            std::unique_lock<std::mutex> lock(idleThreadParams.suspendMutex);
            idleThreadParams.suspendCV.wait(lock, [this] { return !idleThreadParams.isSuspended || idleThreadParams.isExitRequested; });

            if (idleThreadParams.isExitRequested)
                break;
        }        

        // Thread işlemleri burada
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    idleThreadParams.isExited = true;
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] idleThreadFunc() thread exited" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::runThreadFunc(void)
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        AddLog("[CSimEngineRunner] runThreadFunc() thread started");
    }

    while (!runnerThreadParams.isExitRequested)
    {
        // Döngü başlangıç zamanı
        auto loopStartTime = std::chrono::high_resolution_clock::now();

        // -------------------------------------------------------------------------------------------------------------------------------------
        {
            std::unique_lock<std::mutex> lock(runnerThreadParams.suspendMutex);
            runnerThreadParams.suspendCV.wait(lock, [this]{ return !runnerThreadParams.isSuspended || runnerThreadParams.isExitRequested; });

            if (runnerThreadParams.isExitRequested)
                break;
        }

        // -------------------------------------------------------------------------------------------------------------------------------------
        // Zaman değerlerini tutarlı snapshot olarak al (mutex ile)
        uint64_t simulationTimeMSec;
        uint64_t activeSimulationTimeMSec;
        uint64_t suspendedSimulationTimeMSec;

        {
            std::lock_guard<std::mutex> lock(m_timeMutex);
            simulationTimeMSec = m_simulationTimeMSec.load();
            activeSimulationTimeMSec = m_activeSimulationTimeMSec.load();
            suspendedSimulationTimeMSec = m_suspendedSimulationTimeMSec.load();
        }

        // Her 10ms aralığında bir kez log bas (timing kaymalarını tolere et)
        static uint64_t lastLoggedDecade = 0;
        uint64_t currentDecade = simulationTimeMSec / 1;

        if (IsRunning() || IsSuspended() || IsPaused() || IsFreezed())
        {
            if (currentDecade != lastLoggedDecade) {
                std::cout << "simulation time: " << simulationTimeMSec          << "ms" << "\t"
                          << "active time: "     << activeSimulationTimeMSec    << "ms" << "\t"
                          << "suspended time: "  << suspendedSimulationTimeMSec << "ms" << "\t"
                          << std::endl;
                lastLoggedDecade = currentDecade;
            }
        }

        // -------------------------------------------------------------------------------------------------------------------------------------
        {
            switch (m_state.load())
            {
                case EState::Idle:
                {
                    std::lock_guard<std::mutex> lock(coutMutex);
                    std::cout << "[CSimEngineRunner] idleThreadFunc() waiting..." << std::endl;
                }
                break;

                case EState::ResetDone:
                {
                }
                break;

                case EState::Initialized:
                {
                }
                break;

                case EState::Running:
                {
                }
                break;

                case EState::Paused:
                {
                }
                break;

                case EState::Suspended:
                {
                }
                break;

                case EState::Freezed:
                {
                }
                break;

                case EState::Stopped:
                {
                }
                break;

                case EState::Terminated:
                {
                }
                break;
            }

            getCommands();          // ayrı bir threadde yakalanan gönderilmiş olan commandları al
            processCommands();      // commandları işle
            readInputs();           // girişleri oku, her zaman
            parseInputs();          // girişleri işle, her zaman
            processInputBuffer();   // giriş bufferını işle, her zaman

            if (IsRunning())
            {
                // Catch-up mechanism: Sadece suspend sırasında kaybedilen zamanı yakala
                if (suspendedSimulationTimeMSec > 0)
                {
                    // *** CATCH-UP MODE *** Suspend sırasında kaybedilen zamanı hızlıca kapat
                    uint64_t gap = suspendedSimulationTimeMSec;
                    const uint64_t maxCatchUpPerCycle = 100; // Max 100 ms per cycle
                    uint64_t catchUpAmount = (gap > maxCatchUpPerCycle) ? maxCatchUpPerCycle : gap;

                    // Hızlıca catchUpAmount kadar step at (mutex blocking'i önlemek için önce tüm step'leri at)
                    for (uint64_t i = 0; i < catchUpAmount; i++)
                    {
                        stepSimulation();  // Fast-forward simulation (mutex YOK, hızlı!)
                    }

                    // Sonra toplu olarak güncelle (mutex sadece 1 kez!)
                    {
                        std::lock_guard<std::mutex> lock(m_timeMutex);
                        m_activeSimulationTimeMSec.fetch_add(catchUpAmount);
                        m_suspendedSimulationTimeMSec.fetch_sub(catchUpAmount);  // Gap'i azalt
                    }

                    {
                        std::lock_guard<std::mutex> lock(coutMutex);
                        std::cout << "[CSimEngineRunner] Catch-up: +" << catchUpAmount
                            << " ms (remaining gap: " << (gap - catchUpAmount) << " ms)" << std::endl;
                    }
                }
                else
                {
                    // *** NORMAL REALTIME MODE ***
                    stepSimulation();  // Normal 1 step

                    std::lock_guard<std::mutex> lock(m_timeMutex);
                    m_activeSimulationTimeMSec.fetch_add(1);
                }

                createResponses();      // step sonrası cevapları oluştur
                loadResponses();        // cevapları ilgili çıkış bufferlarına yükle
            }
            else if (IsSuspended() || IsPaused() || IsFreezed())
            {
                m_suspendedSimulationTimeMSec.fetch_add(1);
            }
            else
            {

            }

            generateOutputs();      // çıkışları oluştur, her zaman (status/heartbeat)
            writeOutputs();         // çıkışları yaz, her zaman

            FlushLogs();
            ClearLogs();
        }

        // -------------------------------------------------------------------------------------------------------------------------------------
        // Döngü bitiş zamanı ve süre hesaplama (mikrosaniye)
        auto loopEndTime = std::chrono::high_resolution_clock::now();
        auto loopDuration = std::chrono::duration_cast<std::chrono::microseconds>(loopEndTime - loopStartTime);

        // İstatistikler için
        static uint64_t loopCount = 0;
        static int64_t minLoopTime = INT64_MAX;
        static int64_t maxLoopTime = 0;
        static int64_t totalLoopTime = 0;

        loopCount++;
        int64_t currentLoopTime = loopDuration.count();
        totalLoopTime += currentLoopTime;

        if (currentLoopTime < minLoopTime) minLoopTime = currentLoopTime;
        if (currentLoopTime > maxLoopTime) maxLoopTime = currentLoopTime;

        // Her 1000 döngüde bir istatistikleri logla
        if (loopCount % 100 == 0)
        {
            int64_t avgLoopTime = totalLoopTime / loopCount;
            std::stringstream ss;
            ss << "[Loop Stats] Count: " << loopCount
               << " | Avg: " << avgLoopTime << "us"
               << " | Min: " << minLoopTime << "us"
               << " | Max: " << maxLoopTime << "us";
            AddLog(ss.str());
        }

        // -------------------------------------------------------------------------------------------------------------------------------------
        std::this_thread::sleep_for(std::chrono::milliseconds(1));            
    }

    runnerThreadParams.isExited = true;
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] runThreadFunc() thread exited" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::inputThreadFunc(void)
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] inputThreadFunc() thread started" << std::endl;
    }

    while (!inputThreadParams.isExitRequested)
    {
        {
            std::unique_lock<std::mutex> lock(inputThreadParams.suspendMutex);
            inputThreadParams.suspendCV.wait(lock, [this]{ return !inputThreadParams.isSuspended || inputThreadParams.isExitRequested; });

            if (inputThreadParams.isExitRequested)
                break;
        }

        // Thread işlemleri burada

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    inputThreadParams.isExited = true;
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] inputThreadFunc() thread exited" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::outputThreadFunc(void)
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] outputThreadFunc() thread started" << std::endl;
    }

    while (!outputThreadParams.isExitRequested)
    {
        {
            std::unique_lock<std::mutex> lock(outputThreadParams.suspendMutex);
            outputThreadParams.suspendCV.wait(lock, [this]{ return !outputThreadParams.isSuspended || outputThreadParams.isExitRequested; });

            if (outputThreadParams.isExitRequested)
                break;
        }

        // Thread işlemleri burada

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    outputThreadParams.isExited = true;
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[CSimEngineRunner] outputThreadFunc() thread exited" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::startThreads(void)
{
    try
    {
        stopThreads();

        // 1) Parametreleri her start'ta temizle (KRİTİK)
        runnerThreadParams.isExitRequested = false;
        runnerThreadParams.isExited = false;
        runnerThreadParams.isSuspended = false;

        idleThreadParams.isExitRequested = false;
        idleThreadParams.isExited = false;
        idleThreadParams.isSuspended = false;

        inputThreadParams.isExitRequested = false;
        inputThreadParams.isExited = false;
        inputThreadParams.isSuspended = false;

        outputThreadParams.isExitRequested = false;
        outputThreadParams.isExited = false;
        outputThreadParams.isSuspended = false;

        timerThreadParams.isExitRequested = false;
        timerThreadParams.isExited = false;
        timerThreadParams.isSuspended = false;

        // 2) Sonra threadleri yarat
        if (!runnerThreadParams.isStarted)
        {
            runnerThreadParams.pThread = new std::thread(&CSimEngineRunner::runThreadFunc, this);
            runnerThreadParams.isStarted = true;
        }

        if (!idleThreadParams.isStarted)
        {
            idleThreadParams.pThread = new std::thread(&CSimEngineRunner::idleThreadFunc, this);
            idleThreadParams.isStarted = true;
        }

        if (!inputThreadParams.isStarted)
        {
            inputThreadParams.pThread = new std::thread(&CSimEngineRunner::inputThreadFunc, this);
            inputThreadParams.isStarted = true;
        }

        if (!outputThreadParams.isStarted)
        {
            outputThreadParams.pThread = new std::thread(&CSimEngineRunner::outputThreadFunc, this);
            outputThreadParams.isStarted = true;
        }

        if (!timerThreadParams.isStarted)
        {
            timerThreadParams.pThread = new std::thread(&CSimEngineRunner::timerThreadFunc, this);
            timerThreadParams.isStarted = true;
        }
    }
    catch(...)
    {

    }

    return 0;
}

int CSimEngineRunner::stopThreads(void)
{
    try
    {
        int timeout = 5000;
        int elapsed = 0;

        if (runnerThreadParams.isStarted && runnerThreadParams.pThread != nullptr && runnerThreadParams.pThread->joinable())
        {
            runnerThreadParams.isExitRequested = true;
            runnerThreadParams.suspendCV.notify_all();
            elapsed = 0;
            while (!runnerThreadParams.isExited && elapsed < timeout)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                elapsed += 10;
            }
            if (!runnerThreadParams.isExited)
                std::cout << "[CSimEngineRunner] Warning: RunnerThread did not exit within timeout" << std::endl;
            runnerThreadParams.pThread->join();
            delete runnerThreadParams.pThread;
            runnerThreadParams.pThread = nullptr;
            runnerThreadParams.isStarted = false;
        }

        if (idleThreadParams.isStarted && idleThreadParams.pThread != nullptr && idleThreadParams.pThread->joinable())
        {
            idleThreadParams.isExitRequested = true;
            idleThreadParams.suspendCV.notify_all();
            elapsed = 0;
            while (!idleThreadParams.isExited && elapsed < timeout)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                elapsed += 10;
            }
            if (!idleThreadParams.isExited)
                std::cout << "[CSimEngineRunner] Warning: IdleThread did not exit within timeout" << std::endl;
            idleThreadParams.pThread->join();
            delete idleThreadParams.pThread;
            idleThreadParams.pThread = nullptr;
            idleThreadParams.isStarted = false;
        }

        if (inputThreadParams.isStarted && inputThreadParams.pThread != nullptr && inputThreadParams.pThread->joinable())
        {
            inputThreadParams.isExitRequested = true;
            inputThreadParams.suspendCV.notify_all();
            elapsed = 0;
            while (!inputThreadParams.isExited && elapsed < timeout)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                elapsed += 10;
            }
            if (!inputThreadParams.isExited)
                std::cout << "[CSimEngineRunner] Warning: InputThread did not exit within timeout" << std::endl;
            inputThreadParams.pThread->join();
            delete inputThreadParams.pThread;
            inputThreadParams.pThread = nullptr;
            inputThreadParams.isStarted = false;
        }

        if (outputThreadParams.isStarted && outputThreadParams.pThread != nullptr && outputThreadParams.pThread->joinable())
        {
            outputThreadParams.isExitRequested = true;
            outputThreadParams.suspendCV.notify_all();
            elapsed = 0;
            while (!outputThreadParams.isExited && elapsed < timeout)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                elapsed += 10;
            }
            if (!outputThreadParams.isExited)
                std::cout << "[CSimEngineRunner] Warning: OutputThread did not exit within timeout" << std::endl;
            outputThreadParams.pThread->join();
            delete outputThreadParams.pThread;
            outputThreadParams.pThread = nullptr;
            outputThreadParams.isStarted = false;
        }

        if (timerThreadParams.isStarted && timerThreadParams.pThread != nullptr && timerThreadParams.pThread->joinable())
        {
            timerThreadParams.isExitRequested = true;
            timerThreadParams.suspendCV.notify_all();
            elapsed = 0;
            while (!timerThreadParams.isExited && elapsed < timeout)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                elapsed += 10;
            }
            if (!timerThreadParams.isExited)
                std::cout << "[CSimEngineRunner] Warning: TimerThread did not exit within timeout" << std::endl;
            timerThreadParams.pThread->join();
            delete timerThreadParams.pThread;
            timerThreadParams.pThread = nullptr;
            timerThreadParams.isStarted = false;
        }
    }
    catch (...)
    {
        std::cout << "[CSimEngineRunner] Exception in stopThreads()" << std::endl;
    }

    return 0;
}

int CSimEngineRunner::suspendThread(AFS::SThreadParams& threadParams)
{
    if (threadParams.pThread == nullptr)
        return -1;

    {
        std::lock_guard<std::mutex> lock(threadParams.suspendMutex);
        threadParams.isSuspended = true;
    }

    std::cout << "[CSimEngineRunner] Thread suspended" << std::endl;

    return 0;
}

int CSimEngineRunner::resumeThread(AFS::SThreadParams& threadParams)
{
    if (threadParams.pThread == nullptr)
        return -1;

    {
        std::lock_guard<std::mutex> lock(threadParams.suspendMutex);
        threadParams.isSuspended = false;
    }

    threadParams.suspendCV.notify_all();
    std::cout << "[CSimEngineRunner] Thread resumed" << std::endl;

    return 0;
}

int CSimEngineRunner::suspendThreads(void)
{
    std::cout << "[CSimEngineRunner] Suspending all threads..." << std::endl;

    suspendThread(runnerThreadParams);
    suspendThread(idleThreadParams);
    suspendThread(inputThreadParams);
    suspendThread(outputThreadParams);
    suspendThread(timerThreadParams);

    return 0;
}

int CSimEngineRunner::resumeThreads(void)
{
    std::cout << "[CSimEngineRunner] Resuming all threads..." << std::endl;

    resumeThread(runnerThreadParams);
    resumeThread(idleThreadParams);
    resumeThread(inputThreadParams);
    resumeThread(outputThreadParams);
    resumeThread(timerThreadParams);

    return 0;
}

int CSimEngineRunner::readInputs(void)
{
    // TODO: Read inputs from external sources
    return 0;
}

int CSimEngineRunner::parseInputs(void)
{
    // TODO: Parse and validate inputs
    return 0;
}

int CSimEngineRunner::getCommands(void)
{
    // TODO: Get commands from command queue (from another thread)
    return 0;
}

int CSimEngineRunner::processCommands(void)
{
    // TODO: Process received commands
    return 0;
}

int CSimEngineRunner::stepSimulation(void)
{
    // TODO: Advance simulation by one step
    if (pSimEngine != nullptr)
    {
        pSimEngine->step();
    }
    return 0;
}

int CSimEngineRunner::createResponses(void)
{
    // TODO: Create responses after simulation step
    return 0;
}

int CSimEngineRunner::loadResponses(void)
{
    // TODO: Load responses to output buffers
    return 0;
}

int CSimEngineRunner::generateOutputs(void)
{
    // TODO: Generate outputs from simulation state
    return 0;
}

int CSimEngineRunner::writeOutputs(void)
{
    // TODO: Write outputs to external destinations
    return 0;
}

int CSimEngineRunner::processInputBuffer(void)
{
    // TODO: processInputBuffer
    return 0;
}

// Thread-safe logging methods
void CSimEngineRunner::AddLog(const std::string& message)
{
    std::lock_guard<std::mutex> lock(m_logMutex);
    m_logBuffer.push_back(message);
}

void CSimEngineRunner::FlushLogs(void)
{
    std::lock_guard<std::mutex> lock(m_logMutex);

    for (const auto& log : m_logBuffer)
    {
        std::cout << log << std::endl;
    }

    m_logBuffer.clear();
}

void CSimEngineRunner::ClearLogs(void)
{
    std::lock_guard<std::mutex> lock(m_logMutex);
    m_logBuffer.clear();
}


