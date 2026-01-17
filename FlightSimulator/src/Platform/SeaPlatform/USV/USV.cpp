#include "USV.h"

namespace AFS {

CUSV::~CUSV()
{
}

CUSV::CUSV(CSimEngine* pEngine)
    : CSeaPlatform(pEngine)
{
}

void CUSV::update(double deltaTime)
{
}

void CUSV::initialize(void)
{
}

void CUSV::destroy(void)
{
}

int CUSV::Reset(void) { return CSeaPlatform::Reset(); }
int CUSV::Init(void) { return CSeaPlatform::Init(); }
int CUSV::Start(void) { return CSeaPlatform::Start(); }
int CUSV::Stop(void) { return CSeaPlatform::Stop(); }
int CUSV::Terminate(void) { return CSeaPlatform::Terminate(); }
int CUSV::Pause(void) { return CSeaPlatform::Pause(); }
int CUSV::Suspend(void) { return CSeaPlatform::Suspend(); }
int CUSV::Freeze(void) { return CSeaPlatform::Freeze(); }
int CUSV::Resume(void) { return CSeaPlatform::Resume(); }

int CUSV::Update(void) { return CSeaPlatform::Update(); }
int CUSV::UpdateTime(void) { return CSeaPlatform::UpdateTime(); }
int CUSV::UpdateCounters(void) { return CSeaPlatform::UpdateCounters(); }

} // namespace AFS
