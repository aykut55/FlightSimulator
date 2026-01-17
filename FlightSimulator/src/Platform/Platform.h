#pragma once

#include "src/Entity/PhysicalEntity/PhysicalEntity.h"

namespace AFS {

class CPlatform : public CPhysicalEntity
{
public:
    virtual ~CPlatform();
             CPlatform(CSimEngine* pEngine);

    // Lifecycle Implementation
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

    // Legacy Pure Virtuals from CSimObject - Implementing to avoid abstract class error
    virtual void update(double deltaTime) override;
    virtual void initialize() override;
    virtual void destroy() override;

private:
};

} // namespace AFS
