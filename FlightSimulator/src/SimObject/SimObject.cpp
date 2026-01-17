#include "SimObject.h"

namespace AFS {

CSimObject::~CSimObject()
{
}

CSimObject::CSimObject(CSimEngine* pEngine)
    : m_pSimEngine(pEngine)
    , m_objectId(0)
    , m_objectName("")
    , m_objectType(EObjectType::Unknown)
    , m_isActive(true)
    , m_creationTime(0.0)
{
}

} // namespace AFS
