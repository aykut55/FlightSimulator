#pragma once

#include "Ship.h"

namespace AFS {

class CFrigate : public CShip
{
public:
    virtual ~CFrigate();
             CFrigate(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize() override;
    virtual void destroy() override;
};

} // namespace AFS
