#include "Frigate.h"

namespace AFS {

CFrigate::~CFrigate()
{
}

CFrigate::CFrigate(CSimEngine* pEngine)
    : CShip(pEngine)
{
}

void CFrigate::update(double deltaTime)
{
}

void CFrigate::initialize(void)
{
}

void CFrigate::destroy(void)
{
}

int CFrigate::Reset(void) { return CShip::Reset(); }
int CFrigate::Init(void) { return CShip::Init(); }
int CFrigate::Start(void) { return CShip::Start(); }
int CFrigate::Stop(void) { return CShip::Stop(); }
int CFrigate::Terminate(void) { return CShip::Terminate(); }
int CFrigate::Pause(void) { return CShip::Pause(); }
int CFrigate::Suspend(void) { return CShip::Suspend(); }
int CFrigate::Freeze(void) { return CShip::Freeze(); }
int CFrigate::Resume(void) { return CShip::Resume(); }

int CFrigate::Update(void) { return CShip::Update(); }
int CFrigate::UpdateTime(void) { return CShip::UpdateTime(); }
int CFrigate::UpdateCounters(void) { return CShip::UpdateCounters(); }

} // namespace AFS
