#pragma once

#include "Ship.h"

namespace AFS {

class CDestroyer : public CShip
{
public:
    virtual ~CDestroyer();
             CDestroyer(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize() override;
    virtual void destroy() override;
};

} // namespace AFS
