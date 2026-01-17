#include "F35.h"

namespace AFS {

CF35::~CF35()
{
}

CF35::CF35(CSimEngine* pEngine)
    : CAmericanFighter(pEngine)
{
}

void CF35::update(double deltaTime)
{
}

void CF35::initialize(void)
{
}

void CF35::destroy(void)
{
}

int CF35::Reset(void) { return CAmericanFighter::Reset(); }
int CF35::Init(void) { return CAmericanFighter::Init(); }
int CF35::Start(void) { return CAmericanFighter::Start(); }
int CF35::Stop(void) { return CAmericanFighter::Stop(); }
int CF35::Terminate(void) { return CAmericanFighter::Terminate(); }
int CF35::Pause(void) { return CAmericanFighter::Pause(); }
int CF35::Suspend(void) { return CAmericanFighter::Suspend(); }
int CF35::Freeze(void) { return CAmericanFighter::Freeze(); }
int CF35::Resume(void) { return CAmericanFighter::Resume(); }

int CF35::Update(void) { return CAmericanFighter::Update(); }
int CF35::UpdateTime(void) { return CAmericanFighter::UpdateTime(); }
int CF35::UpdateCounters(void) { return CAmericanFighter::UpdateCounters(); }

} // namespace AFS
