#include "UAV.h"

namespace AFS {

CUAV::~CUAV()
{
}

CUAV::CUAV(CSimEngine* pEngine)
    : CAirPlatform(pEngine)
{
}

void CUAV::update(double deltaTime)
{
}

void CUAV::initialize()
{
}

void CUAV::destroy()
{
}

} // namespace AFS
