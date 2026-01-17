#pragma once

#include "Entity.h"

namespace AFS {

class CPhysicalEntity : public CEntity
{
public:
    virtual ~CPhysicalEntity();
             CPhysicalEntity(CSimEngine* pEngine);

protected:

private:
};

} // namespace AFS