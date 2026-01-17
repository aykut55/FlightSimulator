#include "Submarine.h"

namespace AFS {

CSubmarine::~CSubmarine()
{
}

CSubmarine::CSubmarine(CSimEngine* pEngine)
    : CSeaPlatform(pEngine)
{
}

int CSubmarine::Reset(void) { return CSeaPlatform::Reset(); }
int CSubmarine::Init(void) { return CSeaPlatform::Init(); }
int CSubmarine::Start(void) { return CSeaPlatform::Start(); }
int CSubmarine::Stop(void) { return CSeaPlatform::Stop(); }
int CSubmarine::Terminate(void) { return CSeaPlatform::Terminate(); }
int CSubmarine::Pause(void) { return CSeaPlatform::Pause(); }
int CSubmarine::Suspend(void) { return CSeaPlatform::Suspend(); }
int CSubmarine::Freeze(void) { return CSeaPlatform::Freeze(); }
int CSubmarine::Resume(void) { return CSeaPlatform::Resume(); }

int CSubmarine::Update(void) { return CSeaPlatform::Update(); }
int CSubmarine::UpdateTime(void) { return CSeaPlatform::UpdateTime(); }
int CSubmarine::UpdateCounters(void) { return CSeaPlatform::UpdateCounters(); }

} // namespace AFS
