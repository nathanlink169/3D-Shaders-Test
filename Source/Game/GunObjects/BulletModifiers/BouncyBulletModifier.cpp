#include "CommonHeader.h"

BouncyBulletModifier::BouncyBulletModifier()
    : BulletModifier(BM_Bouncy, "Pulsing")
{
    m_SpeedModifier = 0.5f;
    m_TimePassed = 0;
}

BouncyBulletModifier::~BouncyBulletModifier()
{
}

void BouncyBulletModifier::Update(double aDelta)
{
    m_TimePassed += aDelta * 15;

    m_PositionOffset.y = 1.0f / (50.0f * (float)sin((M_PI / 10.0) * (2 * m_TimePassed - 5)) + 51);
}