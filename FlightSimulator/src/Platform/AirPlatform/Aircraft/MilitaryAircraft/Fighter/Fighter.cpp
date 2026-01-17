#include "Fighter.h"

namespace AFS {

CFighter::~CFighter()
{
}

CFighter::CFighter(CSimEngine* pEngine)
    : CMilitaryAircraft(pEngine)
{
    setType(EObjectType::Fighter);
}

void CFighter::update(double deltaTime)
{
}

void CFighter::initialize(void)
{
}

void CFighter::destroy(void)
{
}

int CFighter::Reset(void) { return CMilitaryAircraft::Reset(); }
int CFighter::Init(void) { return CMilitaryAircraft::Init(); }
int CFighter::Start(void) { return CMilitaryAircraft::Start(); }
int CFighter::Stop(void) { return CMilitaryAircraft::Stop(); }
int CFighter::Terminate(void) { return CMilitaryAircraft::Terminate(); }
int CFighter::Pause(void) { return CMilitaryAircraft::Pause(); }
int CFighter::Suspend(void) { return CMilitaryAircraft::Suspend(); }
int CFighter::Freeze(void) { return CMilitaryAircraft::Freeze(); }
int CFighter::Resume(void) { return CMilitaryAircraft::Resume(); }

int CFighter::Update(void) { return CMilitaryAircraft::Update(); }
int CFighter::UpdateTime(void) { return CMilitaryAircraft::UpdateTime(); }
int CFighter::UpdateCounters(void) { return CMilitaryAircraft::UpdateCounters(); }

} // namespace AFS
