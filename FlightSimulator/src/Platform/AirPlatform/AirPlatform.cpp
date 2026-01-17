#include "AirPlatform.h"

namespace AFS {

CAirPlatform::~CAirPlatform()
{
}

CAirPlatform::CAirPlatform(CSimEngine* pEngine)
    : CPlatform(pEngine)
{
}

int CAirPlatform::Reset(void) { return CPlatform::Reset(); }
int CAirPlatform::Init(void) { return CPlatform::Init(); }
int CAirPlatform::Start(void) { return CPlatform::Start(); }
int CAirPlatform::Stop(void) { return CPlatform::Stop(); }
int CAirPlatform::Terminate(void) { return CPlatform::Terminate(); }
int CAirPlatform::Pause(void) { return CPlatform::Pause(); }
int CAirPlatform::Suspend(void) { return CPlatform::Suspend(); }
int CAirPlatform::Freeze(void) { return CPlatform::Freeze(); }
int CAirPlatform::Resume(void) { return CPlatform::Resume(); }

int CAirPlatform::Update(void) { return CPlatform::Update(); }
int CAirPlatform::UpdateTime(void) { return CPlatform::UpdateTime(); }
int CAirPlatform::UpdateCounters(void) { return CPlatform::UpdateCounters(); }

} // namespace AFS
