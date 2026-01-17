#pragma once

namespace AFS {

class ISimObject
{
public:
    virtual ~ISimObject() = default;

    // Lifecycle Actions
    virtual int Reset(void) = 0;
    virtual int Init(void) = 0;
    virtual int Start(void) = 0;
    virtual int Stop(void) = 0;
    virtual int Terminate(void) = 0;

    virtual int Pause(void) = 0;
    virtual int Suspend(void) = 0;
    virtual int Freeze(void) = 0;
    virtual int Resume(void) = 0;

    // Update Methods
    virtual int Update(void) = 0;
    virtual int UpdateTime(void) = 0;
    virtual int UpdateCounters(void) = 0;
};

} // namespace AFS
