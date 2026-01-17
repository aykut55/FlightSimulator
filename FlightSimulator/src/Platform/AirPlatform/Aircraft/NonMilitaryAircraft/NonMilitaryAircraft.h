#pragma once

#include "Aircraft.h"

namespace AFS {

class CNonMilitaryAircraft : public CAircraft
{
public:
    virtual ~CNonMilitaryAircraft();
            CNonMilitaryAircraft(CSimEngine* pEngine);

    // Lifecycle methods
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
