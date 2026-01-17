#pragma once

#include "SeaPlatform.h"

namespace AFS {

class CSubmarine : public CSeaPlatform
{
public:
    virtual ~CSubmarine();
             CSubmarine(CSimEngine* pEngine);

protected:

private:
};

} // namespace AFS
