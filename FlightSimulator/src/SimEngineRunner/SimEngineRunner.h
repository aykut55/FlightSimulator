#pragma once

#include <string>
#include <vector>
#include "src/SimEngine/SimEngine.h"
#include "src/Definitions/ThreadParams.h"
#include "AirPlatform.h"

class CSimEngineRunner 
{
public:
    virtual ~CSimEngineRunner();
             CSimEngineRunner();

    bool IsIdle(void);
    bool IsReset(void);
    bool IsInitialized(void);
    bool IsStarted(void);
    bool IsRunning(void);
    bool IsPaused(void);
    bool IsSuspended(void);
    bool IsFreezed(void);
    bool IsResumed(void);
    bool IsStopped(void);
    bool IsTerminated(void);
    bool IsWaiting(void);

    int Reset(void);
    int Init(void);
    int Start(void);
    int Stop(void);
    int Terminate(void);

    int Pause(void);
    int Suspend(void);
    int Freeze(void);
    int Resume(void);

    int Update(void);
    int UpdateTime(void);
    int UpdateCounters(void);
    int UpdateConfig(void);

    CSimEngine* getSimEngine() const { return pSimEngine; }

    uint64_t GetSimulationTimeMSec(void) const { return m_simulationTimeMSec.load(); }
    uint64_t GetActiveSimulationTimeMSec(void) const { return m_activeSimulationTimeMSec.load(); }

    // Thread-safe logging
    void AddLog(const std::string& message);
    void FlushLogs(void);
    void ClearLogs(void);

protected:

private:
    int timerThreadFunc(void);
    int idleThreadFunc(void);
    int runThreadFunc(void);
    int inputThreadFunc(void);
    int outputThreadFunc(void);

    AFS::SThreadParams timerThreadParams;
    AFS::SThreadParams idleThreadParams;
    AFS::SThreadParams runnerThreadParams;
    AFS::SThreadParams inputThreadParams;
    AFS::SThreadParams outputThreadParams;

    int startThreads(void);
    int stopThreads(void);
    int suspendThreads(void);
    int resumeThreads(void);
    int suspendThread(AFS::SThreadParams& threadParams);
    int resumeThread(AFS::SThreadParams& threadParams);

    int readInputs(void);
    int parseInputs(void);
    int getCommands(void);
    int processCommands(void);
    int stepSimulation(void);
    int createResponses(void);
    int loadResponses(void);
    int generateOutputs(void);
    int writeOutputs(void);
    int processInputBuffer(void);

    std::mutex coutMutex;
    std::mutex m_timeMutex;  // Zaman değişkenlerinin tutarlı snapshot'ı için

    // Thread-safe logging
    std::vector<std::string> m_logBuffer;
    std::mutex m_logMutex;

    CSimEngine* pSimEngine;
    bool shouldExit;
    int maxSteps;
    double maxSimTime;

    // Simulation time in milliseconds (updated by timer thread at 1 ms frequency)
    // This always increments regardless of simulation state
    std::atomic<uint64_t> m_simulationTimeMSec;

    // Active simulation time in milliseconds (only increments when simulation is Running)
    // Pauses during Pause/Suspend/Freeze states
    std::atomic<uint64_t> m_activeSimulationTimeMSec;
    // increments during Pause/Suspend/Freeze states
    std::atomic<uint64_t> m_suspendedSimulationTimeMSec;

    enum class EState : int
    {
        Idle = 0,        // yeni oluşturuldu, reset bile yapılmamış
        ResetDone,       // Reset OK
        Initialized,     // Init OK
        Running,         // Çalışıyor
        Paused,          // Sim pause (threadler durabilir/uyuyabilir)
        Suspended,       // Thread suspend
        Freezed,         // Sim freeze
        Stopped,         // Stop: threadler kapalı
        Terminated       // Shutdown: geri dönüş yok (reset+init şart)
    };

    std::atomic<EState> m_state;
    std::mutex m_stateMutex; // methodlar arası yarışları engellemek için (basit ve güvenli)

    bool IsResetDone(void) const { return m_state.load() == EState::ResetDone; }
    bool IsInitialized(void) const { return m_state.load() == EState::Initialized; }
    bool IsRunning(void) const { return m_state.load() == EState::Running; }
    bool IsStopped(void) const { return m_state.load() == EState::Stopped; }
    bool IsTerminated(void) const { return m_state.load() == EState::Terminated; }
    bool IsTerminatedState(void) const { return m_state.load() == EState::Terminated; }
};
