#include "Destroyer.h"

namespace AFS {

CDestroyer::~CDestroyer()
{
}

CDestroyer::CDestroyer(CSimEngine* pEngine)
    : CShip(pEngine)
{
}

void CDestroyer::update(double deltaTime)
{
}

void CDestroyer::initialize()
{
}

void CDestroyer::destroy()
{
}

} // namespace AFS
