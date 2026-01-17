#pragma once

#include "SeaPlatform.h"

namespace AFS {

class CUSV : public CSeaPlatform
{
public:
    virtual ~CUSV();
             CUSV(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize() override;
    virtual void destroy() override;
};

} // namespace AFS
