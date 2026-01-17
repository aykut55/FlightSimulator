#pragma once

#include "Aircraft.h"

namespace AFS {

class CNonMilitaryAircraft : public CAircraft
{
public:
    virtual ~CNonMilitaryAircraft();
            CNonMilitaryAircraft(CSimEngine* pEngine);

protected:

private:
};

} // namespace AFS
