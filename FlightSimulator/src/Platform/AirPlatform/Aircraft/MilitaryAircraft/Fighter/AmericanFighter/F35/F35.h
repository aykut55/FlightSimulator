#pragma once

#include "AmericanFighter.h"

namespace AFS {

class CF35 : public CAmericanFighter
{
public:
    virtual ~CF35();
            CF35(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize(void) override;
    virtual void destroy(void) override;

protected:

private:
};

} // namespace AFS
