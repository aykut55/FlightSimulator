#pragma once

#include "AirPlatform.h"

namespace AFS {

class CAircraft : public CAirPlatform
{
public:
    virtual ~CAircraft();
             CAircraft(CSimEngine* pEngine);

protected:

private:
};

} // namespace AFS

