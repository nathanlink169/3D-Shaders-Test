#include "CommonHeader.h"

CircleBulletModifier::CircleBulletModifier()
    : BulletModifier(BM_Circle, "Spiralling")
{
    m_SpeedModifier = 0.15f;
    m_TimePassed = 0;
}


CircleBulletModifier::~CircleBulletModifier()
{
}

void CircleBulletModifier::Update(double aDelta)
{
    m_TimePassed += aDelta * 3;

    m_PositionOffset.x = (float)cos(m_TimePassed) * 0.75f;
    m_PositionOffset.y = (float)sin(m_TimePassed) * 0.75f;
}