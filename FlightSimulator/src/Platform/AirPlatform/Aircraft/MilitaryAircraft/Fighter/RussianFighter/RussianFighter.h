#pragma once

#include "Fighter.h"

namespace AFS {

class CRussianFighter : public CFighter
{
public:
    virtual ~CRussianFighter();
             CRussianFighter(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize(void) override;
    virtual void destroy(void) override;
};

} // namespace AFS
