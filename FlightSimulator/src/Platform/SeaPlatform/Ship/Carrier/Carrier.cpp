#include "Carrier.h"

namespace AFS {

CCarrier::~CCarrier()
{
}

CCarrier::CCarrier(CSimEngine* pEngine)
    : CShip(pEngine)
{
}

void CCarrier::update(double deltaTime)
{
}

void CCarrier::initialize(void)
{
}

void CCarrier::destroy(void)
{
}

int CCarrier::Reset(void) { return CShip::Reset(); }
int CCarrier::Init(void) { return CShip::Init(); }
int CCarrier::Start(void) { return CShip::Start(); }
int CCarrier::Stop(void) { return CShip::Stop(); }
int CCarrier::Terminate(void) { return CShip::Terminate(); }
int CCarrier::Pause(void) { return CShip::Pause(); }
int CCarrier::Suspend(void) { return CShip::Suspend(); }
int CCarrier::Freeze(void) { return CShip::Freeze(); }
int CCarrier::Resume(void) { return CShip::Resume(); }

int CCarrier::Update(void) { return CShip::Update(); }
int CCarrier::UpdateTime(void) { return CShip::UpdateTime(); }
int CCarrier::UpdateCounters(void) { return CShip::UpdateCounters(); }

} // namespace AFS
