#include "F16.h"

namespace AFS {

CF16::~CF16()
{
}

CF16::CF16(CSimEngine* pEngine)
    : CAmericanFighter(pEngine)
{
}

void CF16::update(double deltaTime)
{
}

void CF16::initialize(void)
{
}

void CF16::destroy(void)
{
}

int CF16::Reset(void) { return CAmericanFighter::Reset(); }
int CF16::Init(void) { return CAmericanFighter::Init(); }
int CF16::Start(void) { return CAmericanFighter::Start(); }
int CF16::Stop(void) { return CAmericanFighter::Stop(); }
int CF16::Terminate(void) { return CAmericanFighter::Terminate(); }
int CF16::Pause(void) { return CAmericanFighter::Pause(); }
int CF16::Suspend(void) { return CAmericanFighter::Suspend(); }
int CF16::Freeze(void) { return CAmericanFighter::Freeze(); }
int CF16::Resume(void) { return CAmericanFighter::Resume(); }

int CF16::Update(void) { return CAmericanFighter::Update(); }
int CF16::UpdateTime(void) { return CAmericanFighter::UpdateTime(); }
int CF16::UpdateCounters(void) { return CAmericanFighter::UpdateCounters(); }

} // namespace AFS
