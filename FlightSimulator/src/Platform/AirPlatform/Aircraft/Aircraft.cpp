#include "Aircraft.h"
namespace AFS {

CAircraft::~CAircraft()
{
}

CAircraft::CAircraft(CSimEngine* pEngine)
    : CAirPlatform(pEngine)
{
}

}