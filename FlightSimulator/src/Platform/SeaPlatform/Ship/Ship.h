#pragma once

#include "SeaPlatform.h"

namespace AFS {

class CShip : public CSeaPlatform
{
public:
    virtual ~CShip();
             CShip(CSimEngine* pEngine);

protected:

private:
};

} // namespace AFS
