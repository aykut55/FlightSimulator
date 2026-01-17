#include "AttackHelicopter.h"

namespace AFS {

CAttackHelicopter::~CAttackHelicopter()
{
}

CAttackHelicopter::CAttackHelicopter(CSimEngine* pEngine)
    : CHelicopter(pEngine)
{
}

void CAttackHelicopter::update(double deltaTime)
{
}

void CAttackHelicopter::initialize(void)
{
}

void CAttackHelicopter::destroy(void)
{
}

int CAttackHelicopter::Reset(void) { return CHelicopter::Reset(); }
int CAttackHelicopter::Init(void) { return CHelicopter::Init(); }
int CAttackHelicopter::Start(void) { return CHelicopter::Start(); }
int CAttackHelicopter::Stop(void) { return CHelicopter::Stop(); }
int CAttackHelicopter::Terminate(void) { return CHelicopter::Terminate(); }
int CAttackHelicopter::Pause(void) { return CHelicopter::Pause(); }
int CAttackHelicopter::Suspend(void) { return CHelicopter::Suspend(); }
int CAttackHelicopter::Freeze(void) { return CHelicopter::Freeze(); }
int CAttackHelicopter::Resume(void) { return CHelicopter::Resume(); }

int CAttackHelicopter::Update(void) { return CHelicopter::Update(); }
int CAttackHelicopter::UpdateTime(void) { return CHelicopter::UpdateTime(); }
int CAttackHelicopter::UpdateCounters(void) { return CHelicopter::UpdateCounters(); }

} // namespace AFS
