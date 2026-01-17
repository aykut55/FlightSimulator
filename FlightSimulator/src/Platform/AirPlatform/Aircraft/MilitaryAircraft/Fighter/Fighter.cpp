#include "Fighter.h"

namespace AFS {

CFighter::~CFighter()
{
}

CFighter::CFighter(CSimEngine* pEngine)
    : CMilitaryAircraft(pEngine)
{
    setType(EObjectType::Fighter);
}

void CFighter::update(double deltaTime)
{
}

void CFighter::initialize(void)
{
}

void CFighter::destroy(void)
{
}

} // namespace AFS
