#include "Destroyer.h"

namespace AFS {

CDestroyer::~CDestroyer()
{
}

CDestroyer::CDestroyer(CSimEngine* pEngine)
    : CShip(pEngine)
{
}

void CDestroyer::update(double deltaTime)
{
}

void CDestroyer::initialize(void)
{
}

void CDestroyer::destroy(void)
{
}

int CDestroyer::Reset(void) { return CShip::Reset(); }
int CDestroyer::Init(void) { return CShip::Init(); }
int CDestroyer::Start(void) { return CShip::Start(); }
int CDestroyer::Stop(void) { return CShip::Stop(); }
int CDestroyer::Terminate(void) { return CShip::Terminate(); }
int CDestroyer::Pause(void) { return CShip::Pause(); }
int CDestroyer::Suspend(void) { return CShip::Suspend(); }
int CDestroyer::Freeze(void) { return CShip::Freeze(); }
int CDestroyer::Resume(void) { return CShip::Resume(); }

int CDestroyer::Update(void) { return CShip::Update(); }
int CDestroyer::UpdateTime(void) { return CShip::UpdateTime(); }
int CDestroyer::UpdateCounters(void) { return CShip::UpdateCounters(); }

} // namespace AFS
