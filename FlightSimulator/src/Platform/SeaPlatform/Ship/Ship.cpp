#include "Ship.h"

namespace AFS {

CShip::~CShip()
{
}

CShip::CShip(CSimEngine* pEngine)
    : CSeaPlatform(pEngine)
{
}

int CShip::Reset(void) { return CSeaPlatform::Reset(); }
int CShip::Init(void) { return CSeaPlatform::Init(); }
int CShip::Start(void) { return CSeaPlatform::Start(); }
int CShip::Stop(void) { return CSeaPlatform::Stop(); }
int CShip::Terminate(void) { return CSeaPlatform::Terminate(); }
int CShip::Pause(void) { return CSeaPlatform::Pause(); }
int CShip::Suspend(void) { return CSeaPlatform::Suspend(); }
int CShip::Freeze(void) { return CSeaPlatform::Freeze(); }
int CShip::Resume(void) { return CSeaPlatform::Resume(); }

int CShip::Update(void) { return CSeaPlatform::Update(); }
int CShip::UpdateTime(void) { return CSeaPlatform::UpdateTime(); }
int CShip::UpdateCounters(void) { return CSeaPlatform::UpdateCounters(); }

} // namespace AFS
