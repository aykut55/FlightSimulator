#include "AmericanFighter.h"

namespace AFS {

CAmericanFighter::~CAmericanFighter()
{
}

CAmericanFighter::CAmericanFighter(CSimEngine* pEngine)
    : CFighter(pEngine)
{
}

int CAmericanFighter::Reset(void) { return CFighter::Reset(); }
int CAmericanFighter::Init(void) { return CFighter::Init(); }
int CAmericanFighter::Start(void) { return CFighter::Start(); }
int CAmericanFighter::Stop(void) { return CFighter::Stop(); }
int CAmericanFighter::Terminate(void) { return CFighter::Terminate(); }
int CAmericanFighter::Pause(void) { return CFighter::Pause(); }
int CAmericanFighter::Suspend(void) { return CFighter::Suspend(); }
int CAmericanFighter::Freeze(void) { return CFighter::Freeze(); }
int CAmericanFighter::Resume(void) { return CFighter::Resume(); }

int CAmericanFighter::Update(void) { return CFighter::Update(); }
int CAmericanFighter::UpdateTime(void) { return CFighter::UpdateTime(); }
int CAmericanFighter::UpdateCounters(void) { return CFighter::UpdateCounters(); }

} // namespace AFS
