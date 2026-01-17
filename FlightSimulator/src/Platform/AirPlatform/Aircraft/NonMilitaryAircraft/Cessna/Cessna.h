#pragma once

#include "NonMilitaryAircraft.h"

namespace AFS {

class CCessna : public CNonMilitaryAircraft
{
public:
    virtual ~CCessna();
             CCessna(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize(void) override;
    virtual void destroy(void) override;

protected:

private:
};

} // namespace AFS
