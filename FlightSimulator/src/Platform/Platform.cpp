#include "Platform.h"

namespace AFS {

CPlatform::~CPlatform()
{
}

CPlatform::CPlatform(CSimEngine* pEngine)
    : CPhysicalEntity(pEngine)
{
}

} // namespace AFS
