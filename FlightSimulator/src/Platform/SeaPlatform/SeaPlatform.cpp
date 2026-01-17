#include "SeaPlatform.h"

namespace AFS {

CSeaPlatform::~CSeaPlatform()
{
}

CSeaPlatform::CSeaPlatform(CSimEngine* pEngine)
    : CPlatform(pEngine)
{
}

int CSeaPlatform::Reset(void) { return CPlatform::Reset(); }
int CSeaPlatform::Init(void) { return CPlatform::Init(); }
int CSeaPlatform::Start(void) { return CPlatform::Start(); }
int CSeaPlatform::Stop(void) { return CPlatform::Stop(); }
int CSeaPlatform::Terminate(void) { return CPlatform::Terminate(); }
int CSeaPlatform::Pause(void) { return CPlatform::Pause(); }
int CSeaPlatform::Suspend(void) { return CPlatform::Suspend(); }
int CSeaPlatform::Freeze(void) { return CPlatform::Freeze(); }
int CSeaPlatform::Resume(void) { return CPlatform::Resume(); }

int CSeaPlatform::Update(void) { return CPlatform::Update(); }
int CSeaPlatform::UpdateTime(void) { return CPlatform::UpdateTime(); }
int CSeaPlatform::UpdateCounters(void) { return CPlatform::UpdateCounters(); }

} // namespace AFS
