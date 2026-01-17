#pragma once

#include "Submarine.h"

namespace AFS {

class CAttackSubmarine : public CSubmarine
{
public:
    virtual ~CAttackSubmarine();
             CAttackSubmarine(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize() override;
    virtual void destroy() override;
};

} // namespace AFS
