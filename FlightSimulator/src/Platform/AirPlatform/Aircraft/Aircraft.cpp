#include "Aircraft.h"
namespace AFS {

CAircraft::~CAircraft()
{
}

CAircraft::CAircraft(CSimEngine* pEngine)
    : CAirPlatform(pEngine)
{
}

int CAircraft::Reset(void) { return CAirPlatform::Reset(); }
int CAircraft::Init(void) { return CAirPlatform::Init(); }
int CAircraft::Start(void) { return CAirPlatform::Start(); }
int CAircraft::Stop(void) { return CAirPlatform::Stop(); }
int CAircraft::Terminate(void) { return CAirPlatform::Terminate(); }
int CAircraft::Pause(void) { return CAirPlatform::Pause(); }
int CAircraft::Suspend(void) { return CAirPlatform::Suspend(); }
int CAircraft::Freeze(void) { return CAirPlatform::Freeze(); }
int CAircraft::Resume(void) { return CAirPlatform::Resume(); }

int CAircraft::Update(void) { return CAirPlatform::Update(); }
int CAircraft::UpdateTime(void) { return CAirPlatform::UpdateTime(); }
int CAircraft::UpdateCounters(void) { return CAirPlatform::UpdateCounters(); }

}