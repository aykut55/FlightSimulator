#pragma once

#include "Helicopter.h"

namespace AFS {

class CAttackHelicopter : public CHelicopter
{
public:
    virtual ~CAttackHelicopter();
             CAttackHelicopter(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize() override;
    virtual void destroy() override;

protected:

private:
};

} // namespace AFS