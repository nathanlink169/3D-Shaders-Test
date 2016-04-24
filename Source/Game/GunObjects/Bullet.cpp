#include "CommonHeader.h"

Bullet::Bullet(unsigned int renderOrder,Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture)
    : GameObject(renderOrder, aScene, aName, aTag, aPosition, aRotation, aScale, aMesh, aShader, aTexture)
{
    AddPhysicsBox(vec2(0.1f, 0.1f), true,true);
    GetPhysicsBody()->SetGravityScale(0.0f);
    GetPhysicsBody()->SetActive(false);

	SetFilterData(BULLET, ENEMY | BLOCKS);

    m_BasePosition = vec2(0, 0);
    m_Velocity = vec2(0, 0);
}


Bullet::~Bullet()
{
    npw::SafeDeleteVector(m_Modifiers);
}

void Bullet::Update(double TimePassed)
{
    GameObject::Update(TimePassed);

    for (uint i = 0; i < m_Modifiers.size(); i++)
        m_Modifiers[i]->Update(TimePassed);

    m_BasePosition += m_Velocity * (float)TimePassed;

    vec2 pos = GetPositionOffset();

	float mag = pos.Length();
	float angle = (float)npw::ToDegrees(pos.Angle());
	angle += (float)npw::ToDegrees(m_BasePosition.Angle());

	angle = (float)npw::ToRadians(angle);
	pos = vec2(cos(angle) * mag, sin(angle) * mag) + m_BasePosition;

    SetPosition(vec3(pos.x, pos.y, 0));

    m_TimeRemaining -= (float)TimePassed;

    if (m_TimeRemaining < 0.0f)
    {
		ReturnToPool();
    }
}

void Bullet::ReturnToPool()
{
	GameScene* pTest = (GameScene*)m_Scene;
	pTest->ReturnBullet(this);
}

void Bullet::SetModifiers(std::vector<BulletModifier*> aModifiers)
{
    // Ensure that there are no modifiers already in
    npw::SafeDeleteVector(m_Modifiers);

    for (uint i = 0; i < aModifiers.size(); i++)
    {
        BulletModifier* mod;
        switch (aModifiers[i]->GetType())
        {
        case BM_Sin:
            mod = new SinBulletModifier(aModifiers[i]);
            break;
        case BM_Speed:
            mod = new SpeedBulletModifier(aModifiers[i]);
            break;
        case BM_AirMine:
            mod = new AirMineBulletModifier(aModifiers[i]);
            break;
        case BM_Circle:
            mod = new CircleBulletModifier(aModifiers[i]);
            break; 
        case BM_Bouncy:
            mod = new BouncyBulletModifier(aModifiers[i]);
            break;
        case BM_Fire:
            mod = new FireBulletModifier(aModifiers[i]);
            break;
        case BM_Freeze:
            mod = new FreezeBulletModifer(aModifiers[i]);
            break;
        case BM_Poison:
            mod = new PoisonBulletModifer(aModifiers[i]);
            break;
		case BM_SuperSin:
			mod = new SuperSinusoidalBulletModifier(aModifiers[i]);
			break;
		case BM_Damage:
			mod = new DamageBulletModifier(aModifiers[i]);
			break;
        default:
            npw::BreakIfTrue(true);
            break;
        }

        m_Modifiers.push_back(mod);
    }
}

float Bullet::GetAttackPower()
{
	float power = BULLET_BASE_ATTACK_POWER;
	for (unsigned int i = 0; i < m_Modifiers.size(); i++)
		power *= m_Modifiers[i]->GetAttackModifier();
	return power;
}

float Bullet::GetAttackSpeed()
{
	float speed = BULLET_BASE_ATTACK_SPEED;
	for (unsigned int i = 0; i < m_Modifiers.size(); i++)
		speed *= m_Modifiers[i]->GetSpeedModifier();
	return speed;
}

void Bullet::Initialize(vec2 aPosition, vec2 aVelocity, std::vector<BulletModifier*> aModifiers)
{
    SetModifiers(aModifiers);

    m_BasePosition = aPosition;

    GetPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

    SetPosition(vec3(aPosition.x, aPosition.y, 0));
    aVelocity = aVelocity.Normalize();
    GetPhysicsBody()->ApplyLinearImpulse(npw::vec2_To_b2Vec2(aVelocity * GetAttackSpeed()), GetPhysicsBody()->GetWorldCenter(), true);
    GetPhysicsBody()->SetActive(true);

    m_Velocity = npw::b2Vec2_To_vec2(GetPhysicsBody()->GetLinearVelocity());

    m_TimeRemaining = BULLET_LIFETIME;
}

vec2 Bullet::GetPositionOffset()
{
	vec2 offset;
	offset.x = 0;
	offset.y = 0;
	for (unsigned int i = 0; i < m_Modifiers.size(); i++)
	{
		offset.x += m_Modifiers[i]->GetPositionOffset().x;
		offset.y += m_Modifiers[i]->GetPositionOffset().y;
	}
	return offset;
}

std::vector<Effect*> Bullet::GetEffects(bool copy)
{
	std::vector<Effect*> effects;

	for (uint i = 0; i < m_Modifiers.size(); i++)
	{
		Effect* effect = m_Modifiers[i]->GetEffect();
		if (effect != nullptr)
			effects.push_back(effect);
	}

	if (!copy)
		return effects;

	else
	{
		std::vector<Effect*> newEffects;

		for (uint i = 0; i < effects.size(); i++)
			newEffects.push_back(new Effect(effects[i]));
		
		return newEffects;
	}
}

void Bullet::Reset()
{
    SetPosition(Vector3(0, 300, 0));
}