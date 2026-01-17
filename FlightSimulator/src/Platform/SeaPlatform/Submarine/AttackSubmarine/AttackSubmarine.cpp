#include "AttackSubmarine.h"

namespace AFS {

CAttackSubmarine::~CAttackSubmarine()
{
}

CAttackSubmarine::CAttackSubmarine(CSimEngine* pEngine)
    : CSubmarine(pEngine)
{
}

void CAttackSubmarine::update(double deltaTime)
{
}

void CAttackSubmarine::initialize(void)
{
}

void CAttackSubmarine::destroy(void)
{
}

int CAttackSubmarine::Reset(void) { return CSubmarine::Reset(); }
int CAttackSubmarine::Init(void) { return CSubmarine::Init(); }
int CAttackSubmarine::Start(void) { return CSubmarine::Start(); }
int CAttackSubmarine::Stop(void) { return CSubmarine::Stop(); }
int CAttackSubmarine::Terminate(void) { return CSubmarine::Terminate(); }
int CAttackSubmarine::Pause(void) { return CSubmarine::Pause(); }
int CAttackSubmarine::Suspend(void) { return CSubmarine::Suspend(); }
int CAttackSubmarine::Freeze(void) { return CSubmarine::Freeze(); }
int CAttackSubmarine::Resume(void) { return CSubmarine::Resume(); }

int CAttackSubmarine::Update(void) { return CSubmarine::Update(); }
int CAttackSubmarine::UpdateTime(void) { return CSubmarine::UpdateTime(); }
int CAttackSubmarine::UpdateCounters(void) { return CSubmarine::UpdateCounters(); }

} // namespace AFS
