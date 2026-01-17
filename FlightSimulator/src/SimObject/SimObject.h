#pragma once

#include <string>
#include <cstdint>
#include "src/Interfaces/ISimObject.h"

// Forward declaration
class CSimEngine;

enum class EObjectType : int
{
    Unknown = 0,
    SimEngine,
    PhysicalEntity,
    Platform,
    AirPlatform,
    Aircraft,
    Fighter,
    UAV,
    Helicopter,
    SeaPlatform,
    Ship,
    Submarine,
    Weapon,
    Missile,
    Component,
    Sensor
};

namespace AFS {

class CSimObject : public ISimObject
{
protected:
    uint64_t m_objectId;
    std::string m_objectName;
    EObjectType m_objectType;
    bool m_isActive;
    double m_creationTime;
    CSimEngine* m_pSimEngine;  // Reference to SimEngine

public:
    // Constructor
    CSimObject(CSimEngine* pEngine);

    // Virtual destructor
    virtual ~CSimObject();

    // Pure virtual methods - existing
    virtual void update(double deltaTime) = 0;
    virtual void initialize() = 0;
    virtual void destroy() = 0;

    // Getters
    uint64_t getId() const { return m_objectId; }
    std::string getName() const { return m_objectName; }
    EObjectType getType() const { return m_objectType; }
    bool getActive() const { return m_isActive; }
    double getCreationTime() const { return m_creationTime; }
    CSimEngine* getSimEngine() const { return m_pSimEngine; }

    // Setters
    void setName(const std::string& name) { m_objectName = name; }
    void setActive(bool active) { m_isActive = active; }
    void setType(EObjectType type) { m_objectType = type; }

protected:
    // Aligned with SimEngineRunner::EState
    enum class ESimState : int {
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
    ESimState m_simState;

public:
    // Lifecycle Management - Logic aligned with SimEngineRunner
    bool IsIdle(void) const { return m_simState == ESimState::Idle; }
    bool IsReset(void) const { return m_simState == ESimState::ResetDone; }
    bool IsResetDone(void) const { return m_simState == ESimState::ResetDone; }
    bool IsInitialized(void) const { return m_simState == ESimState::Initialized; }
    
    // "IsStarted" means any active state after initialization
    bool IsStarted(void) const { 
        return (m_simState == ESimState::Running ||
                m_simState == ESimState::Paused ||
                m_simState == ESimState::Suspended ||
                m_simState == ESimState::Freezed ||
                m_simState == ESimState::Stopped);
    }

    bool IsRunning(void) const { return m_simState == ESimState::Running; }
    bool IsPaused(void) const { return m_simState == ESimState::Paused; }
    bool IsSuspended(void) const { return m_simState == ESimState::Suspended; }
    bool IsFreezed(void) const { return m_simState == ESimState::Freezed; }
    
    // IsResumed and IsWaiting return false in SimEngineRunner reference
    bool IsResumed(void) const { return false; } 
    bool IsStopped(void) const { return m_simState == ESimState::Stopped; }
    bool IsTerminated(void) const { return m_simState == ESimState::Terminated; }
    bool IsTerminatedState(void) const { return m_simState == ESimState::Terminated; }
    bool IsWaiting(void) const { return false; }

    // Lifecycle Actions - Pure Virtual
    virtual int Reset(void) override = 0;
    virtual int Init(void) override = 0;
    virtual int Start(void) override = 0;
    virtual int Stop(void) override = 0;
    virtual int Terminate(void) override = 0;

    virtual int Pause(void) override = 0;
    virtual int Suspend(void) override = 0;
    virtual int Freeze(void) override = 0;
    virtual int Resume(void) override = 0;

    // Update Methods - Pure Virtual
    virtual int Update(void) override = 0;
    virtual int UpdateTime(void) override = 0;
    virtual int UpdateCounters(void) override = 0;

protected:
    // Protected method to set object ID (called during creation)
    void setId(uint64_t id) { m_objectId = id; }
    void setCreationTime(double time) { m_creationTime = time; }
};

} // namespace AFS



/*
* Belki bunu kullanmak gerekecek...
* 
// Lifecycle Management
    bool IsIdle(void) const;
    bool IsReset(void) const;
    bool IsInitialized(void) const;
    bool IsStarted(void) const;
    bool IsRunning(void) const;
    bool IsPaused(void) const;
    bool IsSuspended(void) const;
    bool IsFreezed(void) const;
    bool IsResumed(void) const;
    bool IsStopped(void) const;
    bool IsTerminated(void) const;
    bool IsWaiting(void) const;
    virtual int Reset(void);
    virtual int Init(void);
    virtual int Start(void);
    virtual int Stop(void);
    virtual int Terminate(void);
    virtual int Pause(void);
    virtual int Suspend(void);
    virtual int Freeze(void);
    virtual int Resume(void);
protected:
    enum class ESimState {
        Unknown = 0,
        Idle,
        Reset,
        Initialized,
        Started,
        Running,
        Paused,
        Suspended,
        Freezed,
        Resumed,
        Stopped,
        Terminated,
        Waiting
    };
    ESimState m_simState;
*/