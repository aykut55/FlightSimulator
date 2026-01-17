#include "NonMilitaryAircraft.h"

namespace AFS {

CNonMilitaryAircraft::~CNonMilitaryAircraft()
{
}

CNonMilitaryAircraft::CNonMilitaryAircraft(CSimEngine* pEngine)
    : CAircraft(pEngine)
{
}

int CNonMilitaryAircraft::Reset(void) { return CAircraft::Reset(); }
int CNonMilitaryAircraft::Init(void) { return CAircraft::Init(); }
int CNonMilitaryAircraft::Start(void) { return CAircraft::Start(); }
int CNonMilitaryAircraft::Stop(void) { return CAircraft::Stop(); }
int CNonMilitaryAircraft::Terminate(void) { return CAircraft::Terminate(); }
int CNonMilitaryAircraft::Pause(void) { return CAircraft::Pause(); }
int CNonMilitaryAircraft::Suspend(void) { return CAircraft::Suspend(); }
int CNonMilitaryAircraft::Freeze(void) { return CAircraft::Freeze(); }
int CNonMilitaryAircraft::Resume(void) { return CAircraft::Resume(); }

int CNonMilitaryAircraft::Update(void) { return CAircraft::Update(); }
int CNonMilitaryAircraft::UpdateTime(void) { return CAircraft::UpdateTime(); }
int CNonMilitaryAircraft::UpdateCounters(void) { return CAircraft::UpdateCounters(); }

} // namespace AFS
