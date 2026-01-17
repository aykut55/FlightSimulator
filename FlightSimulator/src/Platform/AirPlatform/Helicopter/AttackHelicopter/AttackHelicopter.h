#pragma once

#include "Helicopter.h"

namespace AFS {

class CAttackHelicopter : public CHelicopter
{
public:
    virtual ~CAttackHelicopter();
             CAttackHelicopter(CSimEngine* pEngine);

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

    virtual void update(double deltaTime) override;
    virtual void initialize() override;
    virtual void destroy() override;

protected:

private:
};

} // namespace AFS