#include "Helicopter.h"

namespace AFS {

CHelicopter::~CHelicopter()
{
}

CHelicopter::CHelicopter(CSimEngine* pEngine)
    : CAirPlatform(pEngine)
{
}

int CHelicopter::Reset(void) { return CAirPlatform::Reset(); }
int CHelicopter::Init(void) { return CAirPlatform::Init(); }
int CHelicopter::Start(void) { return CAirPlatform::Start(); }
int CHelicopter::Stop(void) { return CAirPlatform::Stop(); }
int CHelicopter::Terminate(void) { return CAirPlatform::Terminate(); }
int CHelicopter::Pause(void) { return CAirPlatform::Pause(); }
int CHelicopter::Suspend(void) { return CAirPlatform::Suspend(); }
int CHelicopter::Freeze(void) { return CAirPlatform::Freeze(); }
int CHelicopter::Resume(void) { return CAirPlatform::Resume(); }

int CHelicopter::Update(void) { return CAirPlatform::Update(); }
int CHelicopter::UpdateTime(void) { return CAirPlatform::UpdateTime(); }
int CHelicopter::UpdateCounters(void) { return CAirPlatform::UpdateCounters(); }

}
