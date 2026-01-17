#pragma once

#include "Platform.h"
#include "src/SimEngine/SimEngine.h"

namespace AFS {

class CAirPlatform : public CPlatform
{
public:
    virtual ~CAirPlatform();
             CAirPlatform(CSimEngine* pEngine);

protected:

private:
};

} // namespace AFS
