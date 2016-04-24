#include "CommonHeader.h"

SuperSinusoidalBulletModifier::SuperSinusoidalBulletModifier()
    : BulletModifier(BM_SuperSin, "Super Sinusoidal")
{
}

SuperSinusoidalBulletModifier::~SuperSinusoidalBulletModifier()
{
}

void SuperSinusoidalBulletModifier::Update(double aDelta)
{
    m_TimePassed += aDelta * 3;

	float x = ((float)m_TimePassed / 3.0f) + 16.434f;
	m_PositionOffset.y = cos((sin(x + (x*cos(x)))) - x);
}