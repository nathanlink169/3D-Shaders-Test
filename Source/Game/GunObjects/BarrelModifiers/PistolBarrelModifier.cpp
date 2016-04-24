#include "CommonHeader.h"

PistolBarrelModifier::PistolBarrelModifier(GameScene* aScene)
    : BarrelModifier(aScene, "Pistol")
{
    m_MaxShotTime *= 0.25f;
}

PistolBarrelModifier::~PistolBarrelModifier()
{
}

std::vector<Bullet*> PistolBarrelModifier::Shoot(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers)
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

std::vector<Bullet*> PistolBarrelModifier::Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers)
{
    Bullet* bullet = GetGameScene()->GetBullet();

    float angle = (float)npw::Random();
    angle += 0.25f;
    angle /= 2.0f;
	npw::LockBetweenRange(angle, 0.0f, 0.5f, -(float)M_PI / 8.0f, (float)M_PI_4 / 8.0f);
	angle += aDirection.Angle();

    vec2 velocity = vec2(cos(angle), sin(angle));

    bullet->Initialize(aPosition, velocity, aBulletModifiers);
    GetGameScene()->AddGameObject(bullet, bullet->GetName());

    std::vector<Bullet*> bullets;
    bullets.push_back(bullet);

    return bullets;
}