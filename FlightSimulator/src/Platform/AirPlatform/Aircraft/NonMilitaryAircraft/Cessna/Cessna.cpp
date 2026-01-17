#include "Cessna.h"

namespace AFS {

CCessna::~CCessna()
{
}

CCessna::CCessna(CSimEngine* pEngine)
    : CNonMilitaryAircraft(pEngine)
{
}

void CCessna::update(double deltaTime)
{
}

void CCessna::initialize(void)
{
}

void CCessna::destroy(void)
{
}

} // namespace AFS
