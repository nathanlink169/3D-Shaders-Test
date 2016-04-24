#include "CommonHeader.h"

PlayerObject::PlayerObject()
{
    m_InitialPosition.Set( 0, 0, 0 );
    m_InitialRotation.Set(0, 0, 0);

    Reset();
}

PlayerObject::PlayerObject(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture)
{
    Init(renderOrder, aScene, aName, aTag, aPosition, aRotation, aScale, aMesh, aShader, aTexture);

	AddPhysicsBox(vec2(1.0f, 1.0f), 1, false);
    GetPhysicsBody()->GetFixtureList()->SetFriction(0);

	SetFilterData(PLAYER, BLOCKS | ITEM | EXIT);
	CreateFootSensor();


	m_Arm = new GameObject( renderOrder, aScene, "PlayerArm", "Player", aPosition, aRotation, Vector3(aScale.x / 2, aScale.y, aScale.z), g_pGame->GetMesh("Box"), g_pGame->GetShader("Texture"), g_pGame->GetTexture("Player_Arm"));
	aScene->AddGameObject(m_Arm, "PlayerArm");

    m_Gun = new Gun(0,(GameScene*)(aScene), "Gun", "Bullet", aPosition, aRotation, aScale / 3, g_pGame->GetMesh("Box"), g_pGame->GetShader("Texture"), g_pGame->GetTexture("Gun"));
    m_Gun->InitializeModifiers(0.0f);
    aScene->AddGameObject(m_Gun, "Gun");

    m_InitialPosition = aPosition;
    m_InitialRotation = aRotation;

	m_UpdateAnimation = false;

    Reset();
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::CreateFootSensor()
{
	GetPhysicsBody()->GetFixtureList()->SetFriction(0);

	b2FixtureDef fixDef; // Set up Foot Fixture
	b2PolygonShape polyShape;

	polyShape.SetAsBox(0.3f, 0.3f, b2Vec2(0.0f, -0.3f), 0.0f);

	fixDef.shape = &polyShape;
	fixDef.density = 1;
	fixDef.isSensor = true;

	b2Fixture* footSensorFixture = GetPhysicsBody()->CreateFixture(&fixDef);
	footSensorFixture->SetUserData(this);
}

void PlayerObject::Draw(int renderorder)
{
    GameObject::Draw(renderorder);
}

void PlayerObject::Update(double TimePassed)
{
    GameObject::Update( TimePassed );

    UpdateGun( TimePassed );

	b2Vec2 vel = m_PhysicsBody->GetLinearVelocity();
    PlayerState oldState = m_CurrentState;

    if (Input::KeyIsPressed('R'))
    {
        Reset();
    }

	if (Input::KeyIsPressed('A'))
	{
		GetPhysicsBody()->SetLinearVelocity(b2Vec2(-PLAYER_MOVE_SPEED, vel.y));
        m_CurrentState = RUN;
		m_Direction = LEFT;
	}

    if (Input::KeyIsPressed('D'))
    {
        GetPhysicsBody()->SetLinearVelocity(b2Vec2(PLAYER_MOVE_SPEED, vel.y));
        m_CurrentState = RUN;
		m_Direction = RIGHT;
	}

    uchar keys[] = { 'A', 'D' };
    if (Input::KeysNotPressed(keys, 2))
    {
		GetPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f, vel.y)); // Player isn't holding left or right, No horizontal movement
		m_UpdateAnimation = true;
	}

	if (Input::KeyIsPressed('W') && m_NumFootContacts > 0) // Jump 
	{
		GetPhysicsBody()->SetLinearVelocity(b2Vec2(vel.x, PLAYER_JUMP_SPEED));
		m_UpdateAnimation = true;
	}


	if (Input::LeftMousePressed())
	{
		m_Gun->Fire( m_GunAngle );
	}
        
	if (Input::KeyJustPressed('E'))
		this->SetGun();

	if (m_Direction == RIGHT)
	{
		m_Gun->SetPosition(Vector3(m_Gun->GetPosition().x, m_Gun->GetPosition().y, m_Position.z - 0.1f));
		m_Arm->SetPosition(Vector3(m_Arm->GetPosition().x, m_Arm->GetPosition().y, m_Position.z - 0.1f));
	}
	else if (m_Direction == LEFT)
	{
		m_Gun->SetPosition(Vector3(m_Gun->GetPosition().x, m_Gun->GetPosition().y, m_Position.z + 0.1f));
		m_Arm->SetPosition(Vector3(m_Arm->GetPosition().x, m_Arm->GetPosition().y, m_Position.z + 0.1f));
	}

	GetPhysicsBody()->SetFixedRotation(true);
	
	GetPhysicsBody()->SetAngularVelocity(0);

	UpdateAnimation();

}

void PlayerObject::SetGun()
{
	int score = ((GameScene*)(m_Scene))->GetMaxScore();

	m_Gun->InitializeModifiers(score / 500.0f);
}

void PlayerObject::UpdateGun(double TimePassed)
{
    vec3 gunPos = GetPosition();

    float gunRadius = 0.5f;

    //Update Gun
	vec2 coords = Input::MouseCoordinates();
    float offset = 300.0f;

    //Center the Coordinates
    coords -= offset;

    vec2 gunOffset = vec2(coords.x, -coords.y);
	float angle = atan2f(coords.y, coords.x);

    gunOffset.Normalize();

	m_GunAngle = gunOffset * gunRadius;

    gunPos.x += gunOffset.x * gunRadius;
    gunPos.y += gunOffset.y * gunRadius;

	m_Gun->SetPosition(gunPos + vec3(-0.18f, 0.2f, 0));
	m_Gun->SetRotation(vec3(0.0f, 0.0f, (float)npw::ToDegrees(angle)));

	m_Arm->SetPosition(m_Position + vec3(-0.22f, 0.2f, -0.002f));
	m_Arm->SetRotation(vec3(0.0f, 0.0f, (float)npw::ToDegrees(angle - M_PI_2)));
}

void PlayerObject::UpdateAnimation()
{
	uchar keys[] = { 'A', 'D' };
	if (Input::KeysJustPressed(keys, 2))
	{
		m_UpdateAnimation = true;
	}

	if (GetPhysicsBody()->GetLinearVelocity() == b2Vec2(0, 0))
	{
		m_CurrentState = IDLE;
	}

	if (m_NumFootContacts == 0)
	{
		m_CurrentState = JUMP;
	}


	AnimatedMesh* setAnim = (AnimatedMesh*)g_pGame->GetMesh("PlayerAnimation");
	std::string dir = (m_Direction == LEFT) ? "_L" : "_R";

	if (m_UpdateAnimation)
	{
		switch (m_CurrentState)
		{
		case IDLE:
			setAnim->SetUserAnimation("Player", "Idle" + dir);
			break;

		case RUN:
			setAnim->SetUserAnimation("Player", "Run" + dir);
			break;

		case JUMP:
			setAnim->SetUserAnimation("Player", "Jump" + dir);
			break;
		}
	}

	m_UpdateAnimation = false;
}

void PlayerObject::Reset()
{
    m_CurrentState = IDLE;

    if (m_PhysicsBody)
    {
        m_PhysicsBody->SetLinearVelocity(b2Vec2(0, 0));
        m_PhysicsBody->SetAngularVelocity(0);
        m_PhysicsBody->SetTransform(b2Vec2(m_InitialPosition.x, m_InitialPosition.y), m_InitialRotation.z * PI / 180);
		m_PhysicsBody->SetAwake(true);

		m_Direction = RIGHT;
		m_NumFootContacts = 0;
    }

}

void PlayerObject::OnBeginContact(b2Contact* contact)
{
	if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
	{
		m_NumFootContacts++;
		m_UpdateAnimation = true;
	}
}

void PlayerObject::OnEndContact(b2Contact* contact)
{
	if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
	{
		m_NumFootContacts--;
	}
}