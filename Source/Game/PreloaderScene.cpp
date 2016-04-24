#include "CommonHeader.h"

PreloaderScene::PreloaderScene()
{
}

PreloaderScene::~PreloaderScene()
{
}

void PreloaderScene::OnSurfaceChanged(unsigned int aWidth, unsigned int aHeight)
{
    Scene::OnSurfaceChanged(aWidth, aHeight);
}

void PreloaderScene::LoadContent()
{
    Scene::LoadContent();

	CreateCameraObject();
	g_pGame->AddShader("PostEffect", new ShaderProgram("Data/Shaders/PostEffect.vert", "Data/Shaders/PostEffect.frag"));
	g_pGame->AddShader("UnlitTexture", new ShaderProgram("Data/Shaders/UnlitTexture.vert", "Data/Shaders/UnlitTexture.frag"));
    g_pGame->AddTexture("LoadingBarOutline", new Material(LoadTexture("Data/Textures/LoadingBarOutline.png"),0.0f));
    g_pGame->AddTexture("LoadingBarProgress", new Material(LoadTexture("Data/Textures/LoadingBarProgress.png"), 0.0f));
	g_pGame->AddMesh("Box", Mesh::CreateBox(Vector2(1, 1)));

	g_pGame->SetCurrentFBODShader(g_pGame->GetShader("PostEffect"));

    AddGameObject(new GameObject(0,this, "Loading Bar Fill", "Loading Bar", vec3(0, 0, 730), vec3(0, 0, 0), vec3(0, 200, 200), g_pGame->GetMesh("Box"), g_pGame->GetShader("UnlitTexture"), g_pGame->GetTexture("LoadingBarProgress")), "Loading Bar Fill");
    AddGameObject(new GameObject(0,this, "Loading Bar Outline", "Loading Bar", vec3(0, 0, 720), vec3(0, 0, 0), vec3(400, 200, 200), g_pGame->GetMesh("Box"), g_pGame->GetShader("UnlitTexture"), g_pGame->GetTexture("LoadingBarOutline")), "Loading Bar Outline");

    CreateLight(vec3(0, 0, -3), Colours::Wheat);

	m_MajorStep = LoadBase;
	m_SubStep = 0;
	m_LoadingLabel = nullptr;
    m_DetailsLabel = nullptr;
}

void PreloaderScene::CreateCameraObject()
{
    m_MainCamera = new CameraObject(0,this, "Camera", "Camera", Vector3(0, 0, -5), Vector3(0, 0, 0), Vector3(1, 1, 1), nullptr, nullptr, nullptr);
}

void PreloaderScene::Update(double aDelta)
{
    Scene::Update(aDelta);

    vec3 scale = m_GameObjects["Loading Bar Fill"]->GetScale();
    scale.x = (float)m_MajorStep / (float)MAX_LOAD_STEPS;
    scale.x *= 400.0f;
    m_GameObjects["Loading Bar Fill"]->SetScale(scale);

	switch (m_MajorStep)
	{
	case LoadBase:
		if (m_SubStep == 0)
		{
			m_SubStep++;
			break;
		}
		LoadBaseLabel();
		m_LoadingLabel = new Label(this, "Loading Label", "Loading", vec3(-100, -150, 720), vec3(0, 0, 0), vec3(20, 20, 20), nullptr, g_pGame->GetShader("Colour"),nullptr);
		m_LoadingLabel->Colour = Colours::Crimson;
		m_LoadingLabel->SetFont("arial");
        m_DetailsLabel = new Label(this, "Details Label", "Loading", vec3(-100, -250, 720), vec3(0, 0, 0), vec3(18, 18, 18), nullptr, g_pGame->GetShader("Colour"), nullptr);
        m_DetailsLabel->Colour = Colours::Crimson;
        m_DetailsLabel->SetFont("arial");
		AddGameObject(m_LoadingLabel, "Loading Label");
        AddGameObject(m_DetailsLabel, "Details Label");
		m_MajorStep++;
        m_SubStep = 0;
		break;
	case LoadShaders:
		m_SubStep = LoadGameShaders(m_SubStep);
        if (m_SubStep == MAX_SHADERS_TO_LOAD)
        {
            m_MajorStep++;
            m_SubStep = 0;
        }
		break;
	case LoadMeshes:
		m_SubStep = LoadGameMeshes(m_SubStep);
        if (m_SubStep == MAX_MESHES_TO_LOAD)
        {
            m_MajorStep++;
            m_SubStep = 0;
        }
		break;
	case LoadTextures:
		m_SubStep = LoadGameTextures(m_SubStep);
        if (m_SubStep == MAX_TEXTURES_TO_LOAD)
        {
            m_MajorStep++;
            m_SubStep = 0;
        }
		break;
	case LoadAudio:
		m_SubStep = LoadGameAudio(m_SubStep);
        if (m_SubStep == MAX_AUDIO_TO_LOAD)
        {
            m_MajorStep++;
            m_SubStep = 0;
        }
		break;
    case LoadFonts:
        if (m_SubStep == 0)
        {
            m_SubStep++;
            break;
        }
        m_SubStep = LoadGameFonts(m_SubStep);
        if (m_SubStep == MAX_FONTS_TO_LOAD)
        {
            m_MajorStep++;
            m_SubStep = 0;
        }
        break;
    case MAX_LOAD_STEPS:
		g_pGame->MainMenu();
		break;
	}
    UpdateLabels();
}

void PreloaderScene::Draw()
{
    m_Matrix.CreatePerspectiveVFoV(CAMERA_PERSPECTIVE_ANGLE, CAMERA_ASPECT_RATIO, CAMERA_NEAR_Z, CAMERA_FAR_Z);
    m_MainCamera->CreateLookAtLeftHandAndReturn(Vector3(0, 1, 0), m_GameObjects["Loading Bar Outline"]->GetPosition());
    Scene::Draw();
}

void PreloaderScene::UpdateLabels()
{
    switch (m_MajorStep)
    {
    case LoadBase:
        break;
    case LoadShaders:
		switch (m_SubStep)
		{
		case TwoDColourShader:
			UpdateLabels("Loading Shaders", "2D Colour");
			break;
		case TextureShader:
			UpdateLabels("Loading Shaders", "Texture");
			break;
		case SkyBoxShader:
			UpdateLabels("Loading Shaders", "Sky Box");
			break;
		case ReflectionShader:
			UpdateLabels("Loading Shaders", "Reflection");
			break;
		case FadedTextureShader:
			UpdateLabels("Loading Shaders", "Faded Texture");
			break;
		case OverlayedTextureShader:
			UpdateLabels("Loading Shaders", "Overlayed Texture");
			break;
		}
        break;
    case LoadMeshes:
        switch (m_SubStep)
        {
        case WaterMesh:
            UpdateLabels("Loading Meshes", "Water");
            break;
        case PlatformMesh:
            UpdateLabels("Loading Meshes", "Platform");
			break;
        case SkyBoxMesh:
            UpdateLabels("Loading Meshes", "SkyBox");
			break;
		case SphereMesh:
			UpdateLabels("Loading Meshes", "Sphere");
            break;
        }
        break;
    case LoadTextures:
        switch (m_SubStep)
        {
        case MegamanTexture:
            UpdateLabels("Loading Textures", "Megaman");
			break;
		case MegamanAnimatedTexture:
			UpdateLabels("Loading Textures", "Megaman Animation");
			break;
		case PlayerArmTexture:
			UpdateLabels("Loading Textures", "Player's Beefy Arm");
			break;
        case WaterTexture:
            UpdateLabels("Loading Textures", "Water");
            break;
		case MetalTexture:
            UpdateLabels("Loading Textures", "Metal");
            break;
        case GunTexture:
            UpdateLabels("Loading Textures", "Gun");
            break;
        case BlackTexture:
            UpdateLabels("Loading Textures", "Black");
            break;
        case EnemyTexture:
            UpdateLabels("Loading Textures", "Enemy");
            break;
        case CubeMapTexture:
            UpdateLabels("Loading Textures", "SkyBox");
			break;
		case ForceFieldTexture:
			UpdateLabels("Loading Textures", "ForceField");
			break;
		case ParticleTexture:
			UpdateLabels("Loading Textures", "Particles");
        }
        break;
    case LoadFonts:
        switch (m_SubStep)
        {
        case ComicFont:
            UpdateLabels("Loading Fonts", "Comic Sans");
            break;
        }
        break;
    case LoadAudio:
        switch (m_SubStep)
        {
        case InitializeAudioManager:
            UpdateLabels("Initializing Managers", "");
            break;
        }
        break;
    }
}

void PreloaderScene::UpdateLabels(std::string aMainLabelString, std::string aDetailsLabelString)
{
    m_LoadingLabel->Text = aMainLabelString;
    m_DetailsLabel->Text = aDetailsLabelString;
}

uint PreloaderScene::LoadGameFonts(uint aStep)
{
    switch (aStep)
    {
    case ComicFont:
        //Label::LoadFont("comic");
        return ++aStep;
    }
	return 0;
}

void PreloaderScene::LoadBaseLabel()
{
	Label::LoadFont("arial");
	g_pGame->AddShader("Colour", new ShaderProgram("Data/Shaders/Colour.vert", "Data/Shaders/Colour.frag"));
}

uint PreloaderScene::LoadGameShaders(uint aStep)
{
	switch(aStep)
	{
	case TwoDColourShader:
		g_pGame->AddShader("2D Colour", new ShaderProgram("Data/Shaders/2D Colour.vert", "Data/Shaders/2D Colour.frag"));
		return ++aStep;
	case TextureShader:
		g_pGame->AddShader("Texture", new ShaderProgram("Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag"));
		return ++aStep;
	case SkyBoxShader:
		g_pGame->AddShader("SkyBox", new ShaderProgram("Data/Shaders/TextureCUBE.vert", "Data/Shaders/TextureCUBE.frag"));
		return ++aStep;
	case ReflectionShader:
		g_pGame->AddShader("Reflection", new ShaderProgram("Data/Shaders/Reflection.vert", "Data/Shaders/Reflection.frag"));
		return ++aStep;
	case FadedTextureShader:
		g_pGame->AddShader("FadedTexture", new ShaderProgram("Data/Shaders/FadedTexture.vert", "Data/Shaders/FadedTexture.frag"));
		return ++aStep;
	case OverlayedTextureShader:
		g_pGame->AddShader("OverlayedTexture", new ShaderProgram("Data/Shaders/OverlayedTexture.vert", "Data/Shaders/OverlayedTexture.frag"));
		return ++aStep;
	}
	return MAX_SHADERS_TO_LOAD;
}

uint PreloaderScene::LoadGameMeshes(uint aStep)
{
	switch (aStep)
	{
    case WaterMesh:
		g_pGame->AddMesh("Water", Mesh::GenerateTexturePlane(15, 15, 300, 300, 50, 50));
		return ++aStep;
    case PlatformMesh:
		g_pGame->AddMesh("Platform", Mesh::GenerateTexturePlatform(1.0f, 1.0f, 3.0f));
		return ++aStep;
    case SkyBoxMesh:
        g_pGame->AddMesh("SkyBox", Mesh::GenerateSkyBox(0.5f));
        return ++aStep;
	case SphereMesh:
		g_pGame->AddMesh("Sphere", Mesh::LoadOBJFile("Data/Objs/sphere.obj",Vector3(0.7f,0.7f,0.7f)));
		return ++aStep;
	case CubeMesh:
		g_pGame->AddMesh("Cube", Mesh::LoadOBJFile("Data/Objs/cube.obj", Vector3(0.7f, 0.7f, 0.7f)));
		return ++aStep;
	}
	return MAX_MESHES_TO_LOAD;
}

uint PreloaderScene::LoadGameTextures(uint aStep)
{
	switch (aStep)
	{
	case MegamanTexture:
		g_pGame->AddTexture("Megaman", new Material(LoadTexture("Data/Textures/Megaman.png"), 2.0f));
		return ++aStep;
	case MegamanAnimatedTexture:
		g_pGame->AddTexture("Megaman_Animated", new Material(LoadTexture("Data/Textures/muscle_man_sprites.png")));
		return ++aStep;
	case PlayerArmTexture:
		g_pGame->AddTexture("Player_Arm", new Material(LoadTexture("Data/Textures/muscle_man_arm.png")));
		return ++aStep;
	case WaterTexture:
		g_pGame->AddTexture("Water", new Material(LoadTexture("Data/Textures/Water.png")));
		return ++aStep;
	case MetalTexture:
		g_pGame->AddTexture("Metal", new Material(LoadTexture("Data/Textures/Metal.png"), 5.0f));
		return ++aStep;
	case GunTexture:
		g_pGame->AddTexture("Gun", new Material(LoadTexture("Data/Textures/gun.png"), 2.0f));
		return ++aStep;
	case BlackTexture:
		g_pGame->AddTexture("Black", new Material(LoadTexture("Data/Textures/Black.png")));
		return ++aStep;
	case EnemyTexture:
		g_pGame->AddTexture("Enemy", new Material(LoadTexture("Data/Textures/Enemy.png")));
		g_pGame->AddTexture("Fire", new Material(LoadTexture("Data/Textures/Fire.png")));
		g_pGame->AddTexture("Poison", new Material(LoadTexture("Data/Textures/Poison.png")));
		return ++aStep;
	case CubeMapTexture:
	{
		const char* names[6] = { "Data/Textures/posx.png", "Data/Textures/negx.png", "Data/Textures/posy.png", "Data/Textures/negy.png", "Data/Textures/posz.png", "Data/Textures/negz.png" };
		g_pGame->AddTexture("SkyBox", new Material(LoadTextureCubemap(names), 15.0f, 0.2f));
		return ++aStep;
	}
	case ForceFieldTexture:
		g_pGame->AddTexture("ForceField", new Material(LoadTexture("Data/Textures/ForceField.png")));
		return ++aStep;
	case ParticleTexture:
		g_pGame->AddTexture("Particles", new Material(LoadTexture("Data/Textures/Particles.png")));
		return ++aStep;
	}
	return MAX_TEXTURES_TO_LOAD;
}

uint PreloaderScene::LoadGameAudio(uint aStep)
{
    switch (aStep)
    {
    case InitializeAudioManager:
        AudioManager::InitializeManager();
        return ++aStep;
    }
	return MAX_AUDIO_TO_LOAD;
}