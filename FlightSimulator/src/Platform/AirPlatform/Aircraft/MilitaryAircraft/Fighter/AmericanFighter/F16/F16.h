#pragma once

#include "AmericanFighter.h"

namespace AFS {

class CF16 : public CAmericanFighter
{
public:
    virtual ~CF16();
            CF16(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize(void) override;
    virtual void destroy(void) override;

protected:

private:
};

} // namespace AFS
