#include "CommonHeader.h"

SawedOffShotgunBarrelModifier::SawedOffShotgunBarrelModifier(GameScene* aScene, uint aNumberOfBullets)
    : BarrelModifier(aScene, "Sawed Off Shotgun")
    , m_NumberOfBullets(aNumberOfBullets)
{
}

SawedOffShotgunBarrelModifier::~SawedOffShotgunBarrelModifier()
{
}

std::vector<Bullet*> SawedOffShotgunBarrelModifier::Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers)
{
    std::vector<Bullet*> bullets;

    for (uint i = 0; i < m_NumberOfBullets; i++)
    {
        bullets.push_back(GetGameScene()->GetBullet());

        float angle = (float)i / (float)m_NumberOfBullets;
        angle += (1.0f / (float)m_NumberOfBullets) / 2.0f;
        npw::LockBetweenRange(angle, 0.0f, 1.0f, -(float)M_PI_2, (float)M_PI_2);
		angle += aDirection.Angle();

        vec2 velocity = vec2((float)(npw::ToDegrees(cos(angle))), (float)(npw::ToDegrees(sin(angle))));
        bullets[i]->Initialize(aPosition, velocity, aBulletModifiers);

        GetGameScene()->AddGameObject(bullets[i], bullets[i]->GetName());
    }

    return bullets;
}