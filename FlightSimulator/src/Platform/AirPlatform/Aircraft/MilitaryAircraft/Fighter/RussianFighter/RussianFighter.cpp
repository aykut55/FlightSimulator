#include "RussianFighter.h"

namespace AFS {

CRussianFighter::~CRussianFighter()
{
}

CRussianFighter::CRussianFighter(CSimEngine* pEngine)
    : CFighter(pEngine)
{
}

void CRussianFighter::update(double deltaTime)
{
}

void CRussianFighter::initialize(void)
{
}

void CRussianFighter::destroy(void)
{
}

int CRussianFighter::Reset(void) { return CFighter::Reset(); }
int CRussianFighter::Init(void) { return CFighter::Init(); }
int CRussianFighter::Start(void) { return CFighter::Start(); }
int CRussianFighter::Stop(void) { return CFighter::Stop(); }
int CRussianFighter::Terminate(void) { return CFighter::Terminate(); }
int CRussianFighter::Pause(void) { return CFighter::Pause(); }
int CRussianFighter::Suspend(void) { return CFighter::Suspend(); }
int CRussianFighter::Freeze(void) { return CFighter::Freeze(); }
int CRussianFighter::Resume(void) { return CFighter::Resume(); }

int CRussianFighter::Update(void) { return CFighter::Update(); }
int CRussianFighter::UpdateTime(void) { return CFighter::UpdateTime(); }
int CRussianFighter::UpdateCounters(void) { return CFighter::UpdateCounters(); }

} // namespace AFS