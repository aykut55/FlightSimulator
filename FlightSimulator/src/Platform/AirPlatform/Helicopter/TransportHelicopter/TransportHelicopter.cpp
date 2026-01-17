#include "TransportHelicopter.h"

namespace AFS {

CTransportHelicopter::~CTransportHelicopter()
{
}

CTransportHelicopter::CTransportHelicopter(CSimEngine* pEngine)
    : CHelicopter(pEngine)
{
}

void CTransportHelicopter::update(double deltaTime)
{
}

void CTransportHelicopter::initialize(void)
{
}

void CTransportHelicopter::destroy(void)
{
}

int CTransportHelicopter::Reset(void) { return CHelicopter::Reset(); }
int CTransportHelicopter::Init(void) { return CHelicopter::Init(); }
int CTransportHelicopter::Start(void) { return CHelicopter::Start(); }
int CTransportHelicopter::Stop(void) { return CHelicopter::Stop(); }
int CTransportHelicopter::Terminate(void) { return CHelicopter::Terminate(); }
int CTransportHelicopter::Pause(void) { return CHelicopter::Pause(); }
int CTransportHelicopter::Suspend(void) { return CHelicopter::Suspend(); }
int CTransportHelicopter::Freeze(void) { return CHelicopter::Freeze(); }
int CTransportHelicopter::Resume(void) { return CHelicopter::Resume(); }

int CTransportHelicopter::Update(void) { return CHelicopter::Update(); }
int CTransportHelicopter::UpdateTime(void) { return CHelicopter::UpdateTime(); }
int CTransportHelicopter::UpdateCounters(void) { return CHelicopter::UpdateCounters(); }

} // namespace AFS
