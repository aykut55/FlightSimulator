#include "Cessna.h"

namespace AFS {

CCessna::~CCessna()
{
}

CCessna::CCessna(CSimEngine* pEngine)
    : CNonMilitaryAircraft(pEngine)
{
}

int CCessna::Reset(void) { return CNonMilitaryAircraft::Reset(); }
int CCessna::Init(void) { return CNonMilitaryAircraft::Init(); }
int CCessna::Start(void) { return CNonMilitaryAircraft::Start(); }
int CCessna::Stop(void) { return CNonMilitaryAircraft::Stop(); }
int CCessna::Terminate(void) { return CNonMilitaryAircraft::Terminate(); }
int CCessna::Pause(void) { return CNonMilitaryAircraft::Pause(); }
int CCessna::Suspend(void) { return CNonMilitaryAircraft::Suspend(); }
int CCessna::Freeze(void) { return CNonMilitaryAircraft::Freeze(); }
int CCessna::Resume(void) { return CNonMilitaryAircraft::Resume(); }

int CCessna::Update(void) { return CNonMilitaryAircraft::Update(); }
int CCessna::UpdateTime(void) { return CNonMilitaryAircraft::UpdateTime(); }
int CCessna::UpdateCounters(void) { return CNonMilitaryAircraft::UpdateCounters(); }

void CCessna::update(double deltaTime)
{
}

void CCessna::initialize(void)
{
}

void CCessna::destroy(void)
{
}

} // namespace AFS
