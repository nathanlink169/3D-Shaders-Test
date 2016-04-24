#include "CommonHeader.h"

AssaultRifleBarrelModifier::AssaultRifleBarrelModifier(GameScene* aScene)
	: BarrelModifier(aScene, "Assault Rifle")
{
    m_MaxShotTime *= 0.4f;
}

AssaultRifleBarrelModifier::~AssaultRifleBarrelModifier()
{
}

std::vector<Bullet*> AssaultRifleBarrelModifier::Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers)
{
    Bullet* bullet = GetGameScene()->GetBullet();

    vec2 velocity = aDirection;

    bullet->Initialize(aPosition, velocity, aBulletModifiers);
    GetGameScene()->AddGameObject(bullet, bullet->GetName());

    std::vector<Bullet*> bullets;
    bullets.push_back(bullet);

    return bullets;
}