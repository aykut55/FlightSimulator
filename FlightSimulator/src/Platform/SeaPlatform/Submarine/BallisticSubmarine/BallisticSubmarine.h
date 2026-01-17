#pragma once

#include "Submarine.h"

namespace AFS {

class CBallisticSubmarine : public CSubmarine
{
public:
    virtual ~CBallisticSubmarine();
             CBallisticSubmarine(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize() override;
    virtual void destroy() override;
};

} // namespace AFS
