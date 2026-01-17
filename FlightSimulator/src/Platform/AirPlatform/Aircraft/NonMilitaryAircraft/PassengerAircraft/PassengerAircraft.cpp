#include "PassengerAircraft.h"

namespace AFS {

CPassengerAircraft::~CPassengerAircraft()
{
}

CPassengerAircraft::CPassengerAircraft(CSimEngine* pEngine)
    : CNonMilitaryAircraft(pEngine)
{
}

void CPassengerAircraft::update(double deltaTime)
{
}

void CPassengerAircraft::initialize(void)
{
}

void CPassengerAircraft::destroy(void)
{
}

} // namespace AFS
