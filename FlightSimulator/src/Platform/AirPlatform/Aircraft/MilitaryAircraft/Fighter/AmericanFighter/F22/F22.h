#pragma once

#include "AmericanFighter.h"

namespace AFS {

class CF22 : public CAmericanFighter
{
public:
    virtual ~CF22();
            CF22(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize(void) override;
    virtual void destroy(void) override;

protected:

private:
};

} // namespace AFS
