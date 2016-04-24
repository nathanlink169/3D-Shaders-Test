#include "CommonHeader.h"

PoisonBulletModifer::PoisonBulletModifer()
    : BulletModifier(BM_Poison, "Poisonous")
{
    m_Effect = new Effect(10.0f, 10.0f, 0.8f, POISION);
}


PoisonBulletModifer::~PoisonBulletModifer()
{
}
