#include "F22.h"

namespace AFS {

CF22::~CF22()
{
}

CF22::CF22(CSimEngine* pEngine)
    : CAmericanFighter(pEngine)
{
}

void CF22::update(double deltaTime)
{
}

void CF22::initialize(void)
{
}

void CF22::destroy(void)
{
}

int CF22::Reset(void) { return CAmericanFighter::Reset(); }
int CF22::Init(void) { return CAmericanFighter::Init(); }
int CF22::Start(void) { return CAmericanFighter::Start(); }
int CF22::Stop(void) { return CAmericanFighter::Stop(); }
int CF22::Terminate(void) { return CAmericanFighter::Terminate(); }
int CF22::Pause(void) { return CAmericanFighter::Pause(); }
int CF22::Suspend(void) { return CAmericanFighter::Suspend(); }
int CF22::Freeze(void) { return CAmericanFighter::Freeze(); }
int CF22::Resume(void) { return CAmericanFighter::Resume(); }

int CF22::Update(void) { return CAmericanFighter::Update(); }
int CF22::UpdateTime(void) { return CAmericanFighter::UpdateTime(); }
int CF22::UpdateCounters(void) { return CAmericanFighter::UpdateCounters(); }

} // namespace AFS
