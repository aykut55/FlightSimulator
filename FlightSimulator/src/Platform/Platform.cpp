#include "Platform.h"

namespace AFS {

CPlatform::~CPlatform()
{
}

CPlatform::CPlatform(CSimEngine* pEngine)
    : CPhysicalEntity(pEngine)
{
}

int CPlatform::Reset(void)
{
    m_simState = ESimState::ResetDone;
    return 0;
}

int CPlatform::Init(void) { return 0; }
int CPlatform::Start(void) { return 0; }
int CPlatform::Stop(void) { return 0; }
int CPlatform::Terminate(void) { return 0; }

int CPlatform::Pause(void) { return 0; }
int CPlatform::Suspend(void) { return 0; }
int CPlatform::Freeze(void) { return 0; }
int CPlatform::Resume(void) { return 0; }

int CPlatform::Update(void) { return 0; }
int CPlatform::UpdateTime(void) { return 0; }
int CPlatform::UpdateCounters(void) { return 0; }

void CPlatform::update(double deltaTime)
{
    // Default implementation
}

void CPlatform::initialize()
{
    // Default implementation
}

void CPlatform::destroy()
{
    // Default implementation
}


} // namespace AFS
