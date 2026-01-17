#pragma once

#include "AirPlatform.h"

namespace AFS {

class CAircraft : public CAirPlatform
{
public:
    virtual ~CAircraft();
             CAircraft(CSimEngine* pEngine);

    // Lifecycle Overrides
    virtual int Reset(void) override;
    virtual int Init(void) override;
    virtual int Start(void) override;
    virtual int Stop(void) override;
    virtual int Terminate(void) override;

    virtual int Pause(void) override;
    virtual int Suspend(void) override;
    virtual int Freeze(void) override;
    virtual int Resume(void) override;

    // Update Methods
    virtual int Update(void) override;
    virtual int UpdateTime(void) override;
    virtual int UpdateCounters(void) override;

protected:

private:
};

} // namespace AFS

