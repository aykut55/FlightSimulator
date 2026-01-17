#pragma once

#include "src/Entity/PhysicalEntity/PhysicalEntity.h"

namespace AFS {

class CPlatform : public CPhysicalEntity
{
public:
    virtual ~CPlatform();
             CPlatform(CSimEngine* pEngine);
protected:

private:
};

} // namespace AFS
