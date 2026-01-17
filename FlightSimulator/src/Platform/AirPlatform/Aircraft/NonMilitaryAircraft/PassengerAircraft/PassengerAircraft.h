#pragma once

#include "NonMilitaryAircraft.h"

namespace AFS {

class CPassengerAircraft : public CNonMilitaryAircraft
{
public:
    virtual ~CPassengerAircraft();
            CPassengerAircraft(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize(void) override;
    virtual void destroy(void) override;

protected:

private:
};

} // namespace AFS
