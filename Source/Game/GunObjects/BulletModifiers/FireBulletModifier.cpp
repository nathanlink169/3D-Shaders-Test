#include "CommonHeader.h"

FireBulletModifier::FireBulletModifier()
    : BulletModifier(BM_Fire, "Flammable")
{
    m_Effect = new Effect(1.5f, 30.0f, 2.0f, FIRE);
    
}


FireBulletModifier::~FireBulletModifier()
{
}
