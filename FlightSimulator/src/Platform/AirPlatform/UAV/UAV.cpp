#include "UAV.h"

namespace AFS {

CUAV::~CUAV()
{
}

CUAV::CUAV(CSimEngine* pEngine)
    : CAirPlatform(pEngine)
{
}

void CUAV::update(double deltaTime)
{
}

void CUAV::initialize()
{
}

void CUAV::destroy()
{
}

int CUAV::Reset(void) { return CAirPlatform::Reset(); }
int CUAV::Init(void) { return CAirPlatform::Init(); }
int CUAV::Start(void) { return CAirPlatform::Start(); }
int CUAV::Stop(void) { return CAirPlatform::Stop(); }
int CUAV::Terminate(void) { return CAirPlatform::Terminate(); }
int CUAV::Pause(void) { return CAirPlatform::Pause(); }
int CUAV::Suspend(void) { return CAirPlatform::Suspend(); }
int CUAV::Freeze(void) { return CAirPlatform::Freeze(); }
int CUAV::Resume(void) { return CAirPlatform::Resume(); }

int CUAV::Update(void) { return CAirPlatform::Update(); }
int CUAV::UpdateTime(void) { return CAirPlatform::UpdateTime(); }
int CUAV::UpdateCounters(void) { return CAirPlatform::UpdateCounters(); }

} // namespace AFS
