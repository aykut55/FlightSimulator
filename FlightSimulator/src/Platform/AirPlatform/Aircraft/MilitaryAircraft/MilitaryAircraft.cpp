#include "MilitaryAircraft.h"

namespace AFS {

CMilitaryAircraft::~CMilitaryAircraft()
{
}

CMilitaryAircraft::CMilitaryAircraft(CSimEngine* pEngine)
    : CAircraft(pEngine)
{
}

int CMilitaryAircraft::Reset(void) { return CAircraft::Reset(); }
int CMilitaryAircraft::Init(void) { return CAircraft::Init(); }
int CMilitaryAircraft::Start(void) { return CAircraft::Start(); }
int CMilitaryAircraft::Stop(void) { return CAircraft::Stop(); }
int CMilitaryAircraft::Terminate(void) { return CAircraft::Terminate(); }
int CMilitaryAircraft::Pause(void) { return CAircraft::Pause(); }
int CMilitaryAircraft::Suspend(void) { return CAircraft::Suspend(); }
int CMilitaryAircraft::Freeze(void) { return CAircraft::Freeze(); }
int CMilitaryAircraft::Resume(void) { return CAircraft::Resume(); }

int CMilitaryAircraft::Update(void) { return CAircraft::Update(); }
int CMilitaryAircraft::UpdateTime(void) { return CAircraft::UpdateTime(); }
int CMilitaryAircraft::UpdateCounters(void) { return CAircraft::UpdateCounters(); }

} // namespace AFS
