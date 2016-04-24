#include "CommonHeader.h"

RifleBarrelModifier::RifleBarrelModifier(GameScene* aScene)
	: BarrelModifier(aScene, "Rifle")
{
}

RifleBarrelModifier::~RifleBarrelModifier()
{
}

std::vector<Bullet*> RifleBarrelModifier::Shoot(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers)
{
	if (Input::LeftMouseJustPressed())
	{
		m_CurrentShotTime = 0;
		//AudioManager::PlaySE("Gunshot");
		return Fire(aPosition, aDirection, aBulletModifiers);
	}

	std::vector<Bullet*> vec;
	return vec;
}

std::vector<Bullet*> RifleBarrelModifier::Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers)
{
    Bullet* bullet = GetGameScene()->GetBullet();

    vec2 velocity = aDirection;

    bullet->Initialize(aPosition, velocity, aBulletModifiers);
    GetGameScene()->AddGameObject(bullet, bullet->GetName());

    std::vector<Bullet*> bullets;
    bullets.push_back(bullet);

    return bullets;
}