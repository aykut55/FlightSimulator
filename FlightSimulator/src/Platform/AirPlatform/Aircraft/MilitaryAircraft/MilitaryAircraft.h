#pragma once

#include "Aircraft.h"

namespace AFS {

class CMilitaryAircraft : public CAircraft
{
public:
    virtual ~CMilitaryAircraft();
            CMilitaryAircraft(CSimEngine* pEngine);

protected:

private:
};

} // namespace AFS
