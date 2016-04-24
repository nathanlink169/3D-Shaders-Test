#include "CommonHeader.h"

Gun::Gun(unsigned int renderOrder,GameScene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture)
    : GameObject(renderOrder, aScene, aName, aTag, aPosition, aRotation, aScale, aMesh, aShader, aTexture)
    , m_BarrelModifier(nullptr)
{
}

Gun::~Gun()
{
	// Do not delete label - scene will do that for us
	npw::SafeDelete(m_BarrelModifier);
	npw::SafeDeleteVector(m_BulletModifiers);
}

void Gun::Update(double aDelta)
{
    m_BarrelModifier->Update(aDelta);
    for (uint i = 0; i < m_BulletModifiers.size(); i++)
        m_BulletModifiers[i]->Update(aDelta);
}

void Gun::InitializeModifiers(float aChance)
{
    npw::SafeDelete(m_BarrelModifier);
    npw::SafeDeleteVector(m_BulletModifiers);

    ///////////////////////
    // V Gun Modifiers V //
    float chance = (float)npw::Random(0.0f, 100.0f) * (float)npw::AbsoluteValue(aChance) + (float)npw::AbsoluteValue((aChance * 10.0f));

	if (chance < 10.6f)
		m_BarrelModifier = new PistolBarrelModifier(((GameScene*)(m_Scene)));
	else if (chance < 23.2f)
		m_BarrelModifier = new RifleBarrelModifier(((GameScene*)(m_Scene)));
    else if (chance < 37.8f)
        m_BarrelModifier = new SawedOffShotgunBarrelModifier(((GameScene*)(m_Scene)), (uint)4 + (uint)aChance);
    else if (chance < 56.4f)
        m_BarrelModifier = new ShotgunBarrelModifier(((GameScene*)(m_Scene)), (uint)2 + (uint)aChance);
    else if (chance < 77.0f)
        m_BarrelModifier = new AssaultRifleBarrelModifier(((GameScene*)(m_Scene)));
    else
        m_BarrelModifier = new SMGBarrelModifier(((GameScene*)(m_Scene)));

    // ^ Gun Modifiers ^ //
    ///////////////////////

    //////////////////////////
    // V Bullet Modifiers V //

	if (npw::Random(0.0, 100.0) * aChance > 50.0)
		m_BulletModifiers.push_back(new FireBulletModifier());
	if (npw::Random(0.0, 100.0) * aChance > 50.0)
		m_BulletModifiers.push_back(new PoisonBulletModifer());
	if (npw::Random(0.0, 100.0) * aChance > 50.0)
		m_BulletModifiers.push_back(new FreezeBulletModifer());
	if (npw::Random(0.0, 100.0) * aChance > 50.0)
		m_BulletModifiers.push_back(new SpeedBulletModifier());
	if (npw::Random(0.0, 100.0) * aChance > 50.0)
		m_BulletModifiers.push_back(new SuperSinusoidalBulletModifier());
	if (npw::Random(0.0, 100.0) * aChance > 50.0)
		m_BulletModifiers.push_back(new SinBulletModifier());
	if (npw::Random(0.0, 100.0) * aChance > 50.0)
		m_BulletModifiers.push_back(new CircleBulletModifier());
    if (npw::Random(0.0, 100.0) * aChance > 50.0)
        m_BulletModifiers.push_back(new BouncyBulletModifier());

	while (true)
	{
		if (npw::Random(0.0, 100.0) * aChance > 50.0)
			m_BulletModifiers.push_back(new DamageBulletModifier());
		else
			break;
	}

	if (npw::Random(0.0, 100.0) * aChance > 90.0)
		m_BulletModifiers.push_back(new AirMineBulletModifier());

    // ^ Bullet Modifiers ^ //
    //////////////////////////

	/////////////////////////
	// V Name Generation V //

	m_Name.clear();
	for (uint i = 0; i < m_BulletModifiers.size(); i++)
	{
		if (m_BulletModifiers[i]->GetType() == BM_Damage)
		{
			uint count = 1;
			bool end = false;
			while (!end)
			{
				if (i + count < m_BulletModifiers.size())
				{
					if (m_BulletModifiers[i + count]->GetType() == BM_Damage)
						count++;
					else
						end = true;
				}
				else
					end = true;
			}

			m_Name = m_Name + m_BulletModifiers[i]->GetName() + "x" + std::to_string(count) + " ";
			i += count;
		}
		else 
			m_Name = m_Name + m_BulletModifiers[i]->GetName() + " ";
	}

	m_Name = m_Name + m_BarrelModifier->GetName();
	// ^ Name Generation ^ //
	/////////////////////////
}

void Gun::Fire(vec2 aDirection)
{
    m_BarrelModifier->Shoot(vec2(GetPosition().x + 0.25f, GetPosition().y -0.1f), aDirection, m_BulletModifiers);
}