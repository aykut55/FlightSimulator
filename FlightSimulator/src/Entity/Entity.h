#pragma once

#include "SimObject.h"

namespace AFS {

class CEntity : public CSimObject
{
public:
    virtual ~CEntity();
            CEntity(CSimEngine* pEngine);

protected:

private:
};

} // namespace AFS