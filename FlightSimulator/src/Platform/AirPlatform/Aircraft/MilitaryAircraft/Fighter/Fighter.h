#pragma once

#include "MilitaryAircraft.h"

namespace AFS {

class CFighter : public CMilitaryAircraft
{
public:
    virtual ~CFighter();
             CFighter(CSimEngine* pEngine);

    virtual void update(double deltaTime) override;
    virtual void initialize(void) override;
    virtual void destroy(void) override;

protected:

private:
};

} // namespace AFS
