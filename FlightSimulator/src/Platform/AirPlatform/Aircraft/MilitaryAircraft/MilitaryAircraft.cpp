#include "MilitaryAircraft.h"

namespace AFS {

CMilitaryAircraft::~CMilitaryAircraft()
{
}

CMilitaryAircraft::CMilitaryAircraft(CSimEngine* pEngine)
    : CAircraft(pEngine)
{
}

} // namespace AFS
