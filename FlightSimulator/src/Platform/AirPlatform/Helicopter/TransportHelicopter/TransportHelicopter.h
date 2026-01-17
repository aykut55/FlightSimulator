#pragma once

#include "Helicopter.h"

namespace AFS {

class CTransportHelicopter : public CHelicopter
{
public:
    virtual ~CTransportHelicopter();
             CTransportHelicopter(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize() override;
    virtual void destroy() override;
};

} // namespace AFS
