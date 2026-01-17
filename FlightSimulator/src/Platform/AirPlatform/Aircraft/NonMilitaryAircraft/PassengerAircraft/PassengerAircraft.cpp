#include "PassengerAircraft.h"

namespace AFS {

CPassengerAircraft::~CPassengerAircraft()
{
}

CPassengerAircraft::CPassengerAircraft(CSimEngine* pEngine)
    : CNonMilitaryAircraft(pEngine)
{
}

int CPassengerAircraft::Reset(void) { return CNonMilitaryAircraft::Reset(); }
int CPassengerAircraft::Init(void) { return CNonMilitaryAircraft::Init(); }
int CPassengerAircraft::Start(void) { return CNonMilitaryAircraft::Start(); }
int CPassengerAircraft::Stop(void) { return CNonMilitaryAircraft::Stop(); }
int CPassengerAircraft::Terminate(void) { return CNonMilitaryAircraft::Terminate(); }
int CPassengerAircraft::Pause(void) { return CNonMilitaryAircraft::Pause(); }
int CPassengerAircraft::Suspend(void) { return CNonMilitaryAircraft::Suspend(); }
int CPassengerAircraft::Freeze(void) { return CNonMilitaryAircraft::Freeze(); }
int CPassengerAircraft::Resume(void) { return CNonMilitaryAircraft::Resume(); }

int CPassengerAircraft::Update(void) { return CNonMilitaryAircraft::Update(); }
int CPassengerAircraft::UpdateTime(void) { return CNonMilitaryAircraft::UpdateTime(); }
int CPassengerAircraft::UpdateCounters(void) { return CNonMilitaryAircraft::UpdateCounters(); }

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
