#include "CommonHeader.h"

BarrelModifier::~BarrelModifier()
{
}

std::vector<Bullet*> BarrelModifier::Shoot(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers)
{
    if (m_CurrentShotTime >= m_MaxShotTime)
    {
        m_CurrentShotTime = 0;
        //AudioManager::PlaySE("Gunshot");
        return Fire(aPosition, aDirection, aBulletModifiers);
    }

    std::vector<Bullet*> vec;
    return vec;
}

void BarrelModifier::Update(double aDelta)
{
    m_CurrentShotTime += (float)aDelta;
}