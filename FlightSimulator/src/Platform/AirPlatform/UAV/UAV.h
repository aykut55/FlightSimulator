#pragma once

#include "AirPlatform.h"

namespace AFS {

class CUAV : public CAirPlatform
{
public:
    virtual ~CUAV();
             CUAV(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize() override;
    virtual void destroy() override;
};

} // namespace AFS
