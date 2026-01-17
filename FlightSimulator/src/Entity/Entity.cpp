#include "Entity.h"

namespace AFS {

CEntity::~CEntity()
{
}

CEntity::CEntity(CSimEngine* pEngine)
    : CSimObject(pEngine)
{
}

} // namespace AFS
