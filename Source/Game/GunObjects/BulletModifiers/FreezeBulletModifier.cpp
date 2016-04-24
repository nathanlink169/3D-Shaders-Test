#include "CommonHeader.h"

FreezeBulletModifer::FreezeBulletModifer()
    : BulletModifier(BM_Poison, "Freezing")
{
    m_Effect = new Effect(2.5f, 10.0f, 0.0f);
}


FreezeBulletModifer::~FreezeBulletModifer()
{
}
