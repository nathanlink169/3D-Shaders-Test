#include "CommonHeader.h"

SpeedBulletModifier::SpeedBulletModifier()
    : BulletModifier(BM_Speed, "Speedy")
{
    m_SpeedModifier *= 1.5;
}


SpeedBulletModifier::~SpeedBulletModifier()
{
}
