#include "CommonHeader.h"

SMGBarrelModifier::SMGBarrelModifier(GameScene* aScene)
	: BarrelModifier(aScene, "SMG")
{
	m_MaxShotTime *= 0.2f;
}

SMGBarrelModifier::~SMGBarrelModifier()
{
}

std::vector<Bullet*> SMGBarrelModifier::Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers)
{
    Bullet* bullet = GetGameScene()->GetBullet();

    float angle = (float)npw::Random();
    angle += 0.5f;
	npw::LockBetweenRange(angle, 0.0f, 1.0f, -(float)M_PI / 8.0f, (float)M_PI_4 / 8.0f);
	angle += aDirection.Angle();

    vec2 velocity = vec2(cos(angle), sin(angle));

    bullet->Initialize(aPosition, velocity, aBulletModifiers);
    GetGameScene()->AddGameObject(bullet, bullet->GetName());

    std::vector<Bullet*> bullets;
    bullets.push_back(bullet);

    return bullets;
}