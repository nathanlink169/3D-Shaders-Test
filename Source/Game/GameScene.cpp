#include "CommonHeader.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete m_HUD;
	delete m_ParticleMesh;
	delete m_SkyBoxMesh;
}

void GameScene::OnSurfaceChanged(unsigned int aWidth, unsigned int aHeight)
{
    Scene::OnSurfaceChanged(aWidth, aHeight);
}

void GameScene::LoadContent()
{
    Scene::LoadContent();

    m_GroundCount = 0;
    m_EnemySpawnRate = 1.0f;
    m_EnemySpawnTimer = 0.0f;
	m_Score = 0;
	m_MaxScore = 0;
    m_ContactListener = new ContactListener();
	m_Box2DWorld->SetContactListener(m_ContactListener);
    
	LoadParticleMeshes();
	LoadAnimatedMeshes();
    LoadGameObjects();
    CreateCameraObject();

	m_HUD = new HUD(this, vec3(0.01f, 0.01f, 0.01f), GetPlayer()->GetGun());

	m_SkyBoxMesh = Mesh::GenerateSkyBox(2.0f);

	m_DrawB2dDebug = false;

    //AudioManager::PlayBGM("Game Theme");
}

void GameScene::CreateCameraObject()
{
    m_MainCamera = new CameraObject(0,this, "Camera", "Camera", Vector3(0, 3, -12), Vector3(0, 0, 0), Vector3(1, 1, 1), nullptr, nullptr, nullptr);
	m_GameObjects["Camera"] = m_MainCamera;

	m_Matrix.CreatePerspectiveVFoV(CAMERA_PERSPECTIVE_ANGLE, CAMERA_ASPECT_RATIO, CAMERA_NEAR_Z, CAMERA_FAR_Z);

	m_Box2DWorld->m_DebugDraw->SetScene(this);
	m_Box2DWorld->m_DebugDraw->SetProjMatrix(&m_Matrix);
}

void GameScene::Update(double aDelta)
{
	m_HUD->Update(aDelta);

	if (Input::KeyJustPressed('B'))
		m_DrawB2dDebug = !m_DrawB2dDebug;

	// Update Animated Meshes
	AnimatedMesh* mesh = (AnimatedMesh*)g_pGame->GetMesh("PlayerAnimation");
    mesh->UpdateAnimationCycles(aDelta);
    Scene::Update(aDelta);
    // Rotate portal mesh
	GameObject* portal = m_GameObjects["DespawnGate"];
	portal->SetRotation(portal->GetRotation() + 40.0f * (float)aDelta);
    // Repool the objects as necessary
    RepoolObjects();

	// Spawn Pickups as necessary
	if (m_SpawnPickupLocs.size() != 0)
	{
		for (uint i = 0; i < m_SpawnPickupLocs.size(); i++)
		{
			PickUp* pickup = m_PickUps->GetNew();
			if (pickup != nullptr)
			{
				pickup->SetPosition(m_SpawnPickupLocs[i]);
				pickup->GetPhysicsBody()->SetActive(true);
				pickup->GetPhysicsBody()->SetAwake(true);
				AddGameObject(pickup, pickup->GetName());
			}
		}
		m_SpawnPickupLocs.clear();
	}

    // Spawn Enemies as necessary
    m_EnemySpawnTimer += (float)aDelta;
    if (m_EnemySpawnTimer >= m_EnemySpawnRate - (m_MaxScore / 2000.0f))
    {
        m_EnemySpawnTimer = 0.0f;
        EnemyObject* enemy = m_Enemies->GetNew();
		if (enemy != nullptr)
		{
			AddGameObject(enemy, enemy->GetName());
			enemy->Reset();
			enemy->SetPosition(Vector3(0, 7, 0));
			enemy->GetPhysicsBody()->SetActive(true);
            enemy->GetPhysicsBody()->SetSleepingAllowed(false);
			enemy->SetHealth(ENEMY_START_HEALTH + (float)((0.05f * (float)GetMaxScore()) - 40.0f) );
		}
    }

	// Update Score
	m_HUD->GetScoreDisplay()->SetScore(long long(m_Score));

	// If Score is Below Zero, End Game
	if (GetScore() < 0)
		g_pGame->EndGame(GetMaxScore());
}

void GameScene::Draw()
{
    //// Have the camera watch the player
    m_MainCamera->CreateLookAtLeftHandAndReturn(Vector3(0, 1, 0), m_GameObjects["Player"]->GetPosition());
	// draw our skybox 
	glDepthMask(false);
	MyMatrix identMat;
	identMat.SetIdentity();
	m_SkyBoxMesh->SetupAttributes(g_pGame->GetShader("SkyBox"));
    m_SkyBoxMesh->SetupUniforms(nullptr, g_pGame->GetShader("SkyBox"), &identMat, &GetCameraMatrix(), &m_Matrix, &identMat, nullptr, g_pGame->GetTexture("SkyBox"), Vector4(0, 0, 0, 0));
	m_SkyBoxMesh->Draw(g_pGame->GetShader("SkyBox"), nullptr);
	//Drawing particle mesh
	m_ParticleMesh->AssembleParticleEmitterData();
	m_ParticleMesh->SetupAttributes(g_pGame->GetShader("UnlitTexture"));
	MyMatrix mat;
	mat.SetIdentity();
	m_ParticleMesh->SetupUniforms(nullptr, g_pGame->GetShader("UnlitTexture"), &mat, &GetCameraMatrix(), &m_Matrix, &mat, g_pGame->GetTexture("Particles"),nullptr, Vector4(1, 1, 1, 1));
	m_ParticleMesh->Draw(g_pGame->GetShader("UnlitTexture"), nullptr);
	glDepthMask(true);
    // Draw all the other game objects
    Scene::Draw();
	m_HUD->Draw();
	// B2D Debug Draw
	if (m_DrawB2dDebug)
		m_Box2DWorld->m_World->DrawDebugData();
}

void GameScene::LoadAnimatedMeshes()
{
	g_pGame->AddMesh("PlayerAnimation", Mesh::CreateBox(Vector2(1, 1), true));

	//init example and adding an animation
	AnimatedMesh* mesh = (AnimatedMesh*)g_pGame->GetMesh("PlayerAnimation");
    mesh->Init(6, 2);

    mesh->AddAnimation("Idle_R", new int[6] { 0, 0, 0, 0, 0, 1 }, 6, 0.2f);
    mesh->AddAnimation("Run_R", new int[4]  { 1, 2, 3, 4 },       4, 0.2f);
	mesh->AddAnimation("Jump_R", new int[1] { 5 }, 1, 0.2f, false );

	mesh->AddAnimation("Idle_L", new int[6] { 6, 6, 6, 6, 6, 7 }, 6, 0.2f);
	mesh->AddAnimation("Run_L", new int[4]  { 7, 8, 9, 10 }, 4, 0.2f);
	mesh->AddAnimation("Jump_L", new int[1] { 11 }, 1, 0.2f, false);
}

void GameScene::CreateGround(Vector3 aPosition, Vector3 aScale, Mesh* aMesh, Material* aTexture)
{
	std::string name = "Ground" + std::to_string(m_GroundCount);

	m_GameObjects[name] = new GameObject(0, this, name, "Ground", aPosition, Vector3(0, 0, 0), aScale,
        aMesh, g_pGame->GetShader("Texture"), aTexture);

    if (aPosition.z == 0)
    {
		m_GameObjects[name]->AddPhysicsBox(vec2(aScale.x, aScale.y), false);
		m_GameObjects[name]->GetPhysicsBody()->SetLinearDamping(500);
		m_GameObjects[name]->SetFilterData(BLOCKS, ENEMY | PLAYER | ITEM | BULLET | EXIT);
    }

    m_GroundCount++;
}
void GameScene::LoadParticleMeshes()
{
	m_ParticleMesh = new ParticleMesh();
}
void GameScene::LoadGameObjects()
{
    // Create a Player
    m_GameObjects["Player"] = new PlayerObject(0,this, "Player", "Player", Vector3(0, 2, 0), Vector3(0, 0, 0), Vector3(1, 1, 1),
        g_pGame->GetMesh("PlayerAnimation"), g_pGame->GetShader("Texture"), g_pGame->GetTexture("Megaman_Animated"));

	//Portal Emitter Effects
	m_GameObjects["DespawnPortalEmitter"] = new PortalEmitter(0,DESPAWN_PORTAL_PARTICLE,0.2f,15.0f,2.0f,this, "DespawnPortalEmitter", "Emitter", Vector3(0.0f, -6.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f),
		nullptr, nullptr, nullptr);
	m_GameObjects["SpawnPortalEmitter"] = new PortalEmitter(0, SPAWN_PORTAL_PARTICLE, 0.2f, 15.0f, 2.0f, this, "SpawnPortalEmitter", "Emitter", Vector3(0.0f, 7.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f),
		nullptr, nullptr, nullptr);

	//Create the spawn for enemies (only 1 in game so did not think a class was needed)
	GameObject* spawnGate = new GameObject(0, this, "SpawnGate", "SpawnGate", Vector3(0, 7, 0), Vector3(0, 0, 0), Vector3(1, 1, 1),
		g_pGame->GetMesh("Sphere"), g_pGame->GetShader("Reflection"), g_pGame->GetTexture("Metal"), g_pGame->GetTexture("SkyBox"));
		m_GameObjects["SpawnGate"] = spawnGate;

	// Create the exit and set it up (only 1 in the game so did not think a class was needed)
	GameObject* despawnGate = new GameObject(0 ,this, "DespawnGate", "DespawnGate", Vector3(0, -6.5, 0), Vector3(0, 0, 0), Vector3(1, 1, 1),
		g_pGame->GetMesh("Sphere"), g_pGame->GetShader("Reflection"),g_pGame->GetTexture("Metal"), g_pGame->GetTexture("SkyBox"));
	despawnGate->AddPhysicsBox(vec2(1, 1), 0, true);
	despawnGate->GetPhysicsBody()->SetGravityScale(0.0f);
	despawnGate->GetPhysicsBody()->SetActive(true);
	despawnGate->SetFilterData(EXIT, ENEMY | BLOCKS | PLAYER);
	m_GameObjects["DespawnGate"] = despawnGate;

	// Create the force field
	GameObject* forceField = new GameObject(4,this, "ForceField", "ForceField", Vector3(0, -6.5, 0), Vector3(0, 0, 0), Vector3(2, 2, 2),
		g_pGame->GetMesh("Sphere"), g_pGame->GetShader("FadedTexture"), g_pGame->GetTexture("ForceField"));
	m_GameObjects["ForceField"] = forceField;

    // Add the player to the animated mesh
    AnimatedMesh* mesh = (AnimatedMesh*)g_pGame->GetMesh("PlayerAnimation");
    mesh->AddUser(m_GameObjects["Player"]);
    mesh->SetUserAnimation("Player", "Idle_R");

	// Add the emitter to the particle mesh
	m_ParticleMesh->AddEmitter((ParticleEmitter*)m_GameObjects["DespawnPortalEmitter"]);
	m_ParticleMesh->AddEmitter((ParticleEmitter*)m_GameObjects["SpawnPortalEmitter"]);

    // Create the Pool of Bullets
    m_Bullets = new Pool<Bullet>();
    for (uint i = 0; i < 200; i++)
        m_Bullets->AddNewObject(new Bullet(0,this, "Bullet" + std::to_string(i), "Bullet", Vector3(0, 200, 0), Vector3(0, 0, 0), Vector3(0.25, 0.25, 0.25),
        g_pGame->GetMesh("Box"), g_pGame->GetShader("Texture"), g_pGame->GetTexture("Megaman")));

    // Create the Pool of Enemies
    m_Enemies = new Pool<EnemyObject>();
    for (uint i = 0; i < 1000; i++)
        m_Enemies->AddNewObject(new EnemyObject(0,this, "Enemy" + std::to_string(i), "Enemy", Vector3(0, 300, 0), Vector3(0, 0, 0), Vector3(1, 1, 1),
        g_pGame->GetMesh("Box"), g_pGame->GetShader("Texture"), g_pGame->GetTexture("Enemy")));

    // Create the Pool of Weapon Pickups
	m_PickUps = new Pool<PickUp>();
	for (uint i = 0; i < 50; i ++)
		m_PickUps->AddNewObject(new PickUp(0,this, "PickUp" + std::to_string(i), "PickUp", Vector3(0, 50, 0), Vector3(0, 0, 0), Vector3(1, 1, 1),
		g_pGame->GetMesh("Box"), g_pGame->GetShader("Texture"), g_pGame->GetTexture("Megaman")));

    // Create the lights in the game
	CreateLight(vec3(-4, 2, -3), Colours::Red);
	CreateLight(vec3(0, 1, -3), Colours::Yellow);
	CreateLight(vec3(4, 2, -3), Colours::Blue);
	CreateLight(vec3(3, 7, -3), Colours::Blue);
	CreateLight(vec3(-4, 7, -3), Colours::Red);
	CreateLight(vec3(3, -4, -3), Colours::Yellow);
	CreateLight(vec3(-3, -4, -3), Colours::Yellow);
	CreateLight(vec3(-2, -6.5, -2), Colours::Blue);
	CreateLight(vec3(2, -6.5, -2), Colours::Red);
    // Arena - Outlines
    CreateGround(vec3(0, -7.5, 0), vec3(11, 1, 1), g_pGame->GetMesh("Platform"), g_pGame->GetTexture("Metal"));
    CreateGround(vec3(-5, 0, 0), vec3(1, 14, 1), g_pGame->GetMesh("Platform"), g_pGame->GetTexture("Metal"));
    CreateGround(vec3( 5, 0, 0), vec3(1, 14, 1), g_pGame->GetMesh("Platform"), g_pGame->GetTexture("Metal"));
    // Arena - Walls
    CreateGround(vec3(-3, 6.5, 0), vec3(3.5, 1, 1), g_pGame->GetMesh("Platform"), g_pGame->GetTexture("Metal"));
    CreateGround(vec3( 3, 6.5, 0), vec3(3.5, 1, 1), g_pGame->GetMesh("Platform"), g_pGame->GetTexture("Metal"));
    CreateGround(vec3( 0,   4, 0), vec3(5.5, 1, 1), g_pGame->GetMesh("Platform"), g_pGame->GetTexture("Metal"));
    CreateGround(vec3(-3, 1.5, 0), vec3(3.5, 1, 1), g_pGame->GetMesh("Platform"), g_pGame->GetTexture("Metal"));
    CreateGround(vec3( 3, 1.5, 0), vec3(3.5, 1, 1), g_pGame->GetMesh("Platform"), g_pGame->GetTexture("Metal"));
    CreateGround(vec3( 0,  -1, 0), vec3(5.5, 1, 1), g_pGame->GetMesh("Platform"), g_pGame->GetTexture("Metal"));
    CreateGround(vec3(-3,-3.5, 0), vec3(3.5, 1, 1), g_pGame->GetMesh("Platform"), g_pGame->GetTexture("Metal"));
    CreateGround(vec3( 3,-3.5, 0), vec3(3.5, 1, 1), g_pGame->GetMesh("Platform"), g_pGame->GetTexture("Metal"));
}

void GameScene::SpawnPickUp(EnemyObject* aSpawner)
{
    m_SpawnPickupLocs.push_back(aSpawner->GetPosition());
}

void GameScene::RepoolObjects()
{
    // Repool the Bullets
    for (uint i = 0; i < m_RepoolBullets.size(); i++)
    {
        m_GameObjects.erase(m_RepoolBullets.at(i)->GetName()); // remove from Scene
		m_RepoolBullets.at(i)->GetPhysicsBody()->SetActive(false);
        m_Bullets->Return(m_RepoolBullets.at(i));       // return to Pool
        m_RepoolBullets.erase(m_RepoolBullets.begin() + i); // remove from Repool vector
        i = 0;
    }
    // Repool the Enemies
    for (uint i = 0; i < m_RepoolEnemies.size(); i++)
    {
        m_GameObjects.erase(m_RepoolEnemies.at(i)->GetName()); // remove from Scene
        m_Enemies->Return(m_RepoolEnemies.at(i));       // return to Pool
        m_RepoolEnemies.erase(m_RepoolEnemies.begin() + i); // remove from Repool vector
        i = 0;
    }

    // Repool the Pickups
    for (uint i = 0; i < m_RepoolPickups.size(); i++)
    {
        m_GameObjects.erase(m_RepoolPickups.at(i)->GetName());
        m_PickUps->Return(m_RepoolPickups.at(i));
        m_RepoolPickups.erase(m_RepoolPickups.begin() + i);
        i = 0;
    }
}