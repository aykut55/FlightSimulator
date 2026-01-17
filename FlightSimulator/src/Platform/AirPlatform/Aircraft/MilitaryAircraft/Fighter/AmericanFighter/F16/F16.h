#pragma once

#include "AmericanFighter.h"

namespace AFS {

class CF16 : public CAmericanFighter
{
public:
    virtual ~CF16();
            CF16(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize(void) override;
    virtual void destroy(void) override;

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
