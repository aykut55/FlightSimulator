#include "BallisticSubmarine.h"

namespace AFS {

CBallisticSubmarine::~CBallisticSubmarine()
{
}

CBallisticSubmarine::CBallisticSubmarine(CSimEngine* pEngine)
    : CSubmarine(pEngine)
{
}

void CBallisticSubmarine::update(double deltaTime)
{
}

void CBallisticSubmarine::initialize(void)
{
}

void CBallisticSubmarine::destroy(void)
{
}

int CBallisticSubmarine::Reset(void) { return CSubmarine::Reset(); }
int CBallisticSubmarine::Init(void) { return CSubmarine::Init(); }
int CBallisticSubmarine::Start(void) { return CSubmarine::Start(); }
int CBallisticSubmarine::Stop(void) { return CSubmarine::Stop(); }
int CBallisticSubmarine::Terminate(void) { return CSubmarine::Terminate(); }
int CBallisticSubmarine::Pause(void) { return CSubmarine::Pause(); }
int CBallisticSubmarine::Suspend(void) { return CSubmarine::Suspend(); }
int CBallisticSubmarine::Freeze(void) { return CSubmarine::Freeze(); }
int CBallisticSubmarine::Resume(void) { return CSubmarine::Resume(); }

int CBallisticSubmarine::Update(void) { return CSubmarine::Update(); }
int CBallisticSubmarine::UpdateTime(void) { return CSubmarine::UpdateTime(); }
int CBallisticSubmarine::UpdateCounters(void) { return CSubmarine::UpdateCounters(); }

} // namespace AFS
