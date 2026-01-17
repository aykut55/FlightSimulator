#pragma once

#include "Ship.h"

namespace AFS {

class CCarrier : public CShip
{
public:
    virtual ~CCarrier();
             CCarrier(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize() override;
    virtual void destroy() override;
};

} // namespace AFS
