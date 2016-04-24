#include "CommonHeader.h"

DamageBulletModifier::DamageBulletModifier()
    : BulletModifier(BM_Damage, "Damaging")
{
    m_AttackModifier *= 1.5;
}


DamageBulletModifier::~DamageBulletModifier()
{
}
