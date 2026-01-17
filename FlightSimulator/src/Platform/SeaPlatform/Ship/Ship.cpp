#include "Ship.h"

namespace AFS {

CShip::~CShip()
{
}

CShip::CShip(CSimEngine* pEngine)
    : CSeaPlatform(pEngine)
{
}

} // namespace AFS
