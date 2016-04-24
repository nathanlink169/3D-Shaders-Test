#include "CommonHeader.h"

SinBulletModifier::SinBulletModifier()
    : BulletModifier(BM_Sin, "Oscillating")
{
}

SinBulletModifier::~SinBulletModifier()
{
}

void SinBulletModifier::Update(double aDelta)
{
    m_TimePassed += aDelta * 3;

    m_PositionOffset.y = (float)sin(m_TimePassed) * 0.75f;
}