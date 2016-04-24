#include "CommonHeader.h"

AirMineBulletModifier::AirMineBulletModifier()
    : BulletModifier(BM_AirMine, "Mine Laying")
{
    m_SpeedModifier *= 0;
}


AirMineBulletModifier::~AirMineBulletModifier()
{
}
