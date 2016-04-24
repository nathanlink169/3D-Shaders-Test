#include "CommonHeader.h"

EnemyObject::EnemyObject()
{
    m_InitialPosition.Set(0, 0, 0);
    m_InitialRotation.Set(0, 0, 0);

    Reset();
}

EnemyObject::EnemyObject(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture)
{
    Init(renderOrder, aScene, aName, aTag, aPosition, aRotation, aScale, aMesh, aShader, aTexture);

    AddPhysicsBox(vec2(1, 1), true);
    GetPhysicsBody()->SetFixedRotation(true);
    GetPhysicsBody()->GetFixtureList()->SetFriction(0.0f);

    SetFilterData(ENEMY, BULLET | BLOCKS | EXIT);

    m_InitialPosition = aPosition;
    m_InitialRotation = aRotation;

	m_FlagForDespawn = false;

    Reset();
}

EnemyObject::~EnemyObject()
{
}

void EnemyObject::Draw(int renderorder)
{
    GameObject::Draw(renderorder);
}

void EnemyObject::Update(double TimePassed)
{
    GameObject::Update(TimePassed);

    GetPhysicsBody()->SetLinearVelocity(b2Vec2(MOVE_SPEED * m_Direction * GetSpeedModifier(), m_PhysicsBody->GetLinearVelocity().y));

    m_Health -= GetPoisonRate() * (float)TimePassed;

    for (uint i = 0; i < m_Effects.size(); i++)
    {
        m_Effects[i]->ReduceTime((float)TimePassed);
        if (m_Effects[i]->GetTimeRemaining() <= 0)
        {
            npw::SafeDelete(m_Effects[i]);
            m_Effects.erase(m_Effects.begin() + i);
            UpdateEffects();
            i--;
        }
    }

    if (m_Health <= 0.0f) // Enemy Dies
	{
		GameScene* gameScene = (GameScene*)m_Scene;

        if (npw::Random() <= ENEMY_SPAWN_PICKUP_RATE)
        {
			gameScene->SpawnPickUp(this);
        }

		gameScene->AddToScore(10);

        ReturnToPool();
    }

	if (m_FlagForDespawn)
	{
		ReturnToPool();
		m_FlagForDespawn = false;
	}
}

void EnemyObject::ReturnToPool()
{
    GameScene* pTest = (GameScene*)m_Scene;
    pTest->ReturnEnemy(this);
}
void EnemyObject::Reset()
{
    m_ShaderProgram = g_pGame->GetShader("Texture");
    m_Direction = (npw::Random(0, 2) == 0) ? -1 : 1;
    m_Health = ENEMY_START_HEALTH;
    npw::SafeDeleteVector(m_Effects);

    if (m_PhysicsBody)
    {
        m_PhysicsBody->SetLinearVelocity(b2Vec2(0, 0));
        m_PhysicsBody->SetAngularVelocity(0);
        m_PhysicsBody->SetTransform(b2Vec2(m_InitialPosition.x, m_InitialPosition.y), m_InitialRotation.z * PI / 180);
        m_PhysicsBody->SetAwake(true);
        m_PhysicsBody->SetActive(false);
    }

}


void EnemyObject::AddEffect(Effect* effect)
{
    m_Effects.push_back(effect);
    UpdateEffects();
}

void EnemyObject::UpdateEffects()
{
    for (int i = 0; i < m_Effects.size(); i++)
    {
        switch (m_Effects[i]->GetDamageType())
        {
        case FIRE:
        {
            m_ShaderProgram = g_pGame->GetShader("OverlayedTexture");
            m_SecondaryTextureHandle = g_pGame->GetTexture("Fire");
            return;
        }
        case POISION:
        {
            m_ShaderProgram = g_pGame->GetShader("OverlayedTexture");
            m_SecondaryTextureHandle = g_pGame->GetTexture("Poison");
            return;
        }
        }
    }
    m_ShaderProgram = g_pGame->GetShader("Texture");
    m_SecondaryTextureHandle = nullptr;
}

void EnemyObject::OnBeginContact(b2Contact* contact)
{
    GameObject* object = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
    if (object == this)
        object = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

    b2Vec2 coll = contact->GetCollisionNormal();
    if (npw::AbsoluteValue(coll.x) > npw::AbsoluteValue(coll.y))
        m_Direction *= -1;
    if (object->GetTag() == "Bullet")
    {
        Bullet* bullet = (Bullet*)(object);
        m_Health -= bullet->GetAttackPower();

        std::vector<Effect*> effects = bullet->GetEffects();

        for (uint i = 0; i < effects.size(); i++)
            AddEffect(effects[i]);

        bullet->ReturnToPool();
    }
	else if (object->GetTag() == "DespawnGate")
	{
		m_FlagForDespawn = true;
		g_pGame->TurnOnDamageEffect();
		GameScene* gameScene = (GameScene*)m_Scene;
		gameScene->AddToScore(-50);
	}


}

void EnemyObject::OnEndContact(b2Contact* contact)
{

}

float EnemyObject::GetSpeedModifier()
{
    uint i = 0;
    float mod = 1;
    for (; i < m_Effects.size(); i++)
        mod *= m_Effects[i]->GetSpeedModifier();

    if (mod != 0 && m_Effects.size() != 0)
        mod = (float)npw::NthRoot(i, mod);

    return mod;
}

float EnemyObject::GetPoisonRate()
{
    float rate = 0;
    for (uint i = 0; i < m_Effects.size(); i++)
        rate += m_Effects[i]->GetPoisonRate();
    return rate;
}