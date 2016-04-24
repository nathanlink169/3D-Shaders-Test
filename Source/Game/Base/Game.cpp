#include "CommonHeader.h"

Game* g_pGame = 0;

extern bool g_KeyStates[256];
extern bool g_OldKeyStates[256];

Game::Game()
{
    g_pGame = this;

    m_Scene = 0;

	m_DamageEffectOn = false;
}

Game::~Game()
{
    delete m_Scene;
	delete m_FrameBufferMesh;
    for each( auto iterator in m_Meshes )
        delete iterator.second;

    for each( auto iterator in m_Shaders )
        delete iterator.second;

    for each(auto iterator in m_Textures)
    {
        glDeleteTextures(1, &iterator.second->TextureHandle);
        delete iterator.second;
    }
}

void Game::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    glViewport( 0, 0, width, height );

    m_WindowWidth = width;
    m_WindowHeight = height;
}

void Game::LoadContent()
{
    //turn on back face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    // turn on depth buffer testing.
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );

    // turn on alpha blending.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_FBOD = new FBODefinition();
    m_FBOD->Setup(1024, 1024);

    AddTexture("PostEffect", new Material(m_FBOD->m_ColorTextureHandle));
	m_FrameBufferMesh = Mesh::CreateBox(Vector2(2, 2));

    m_Scene = new PreloaderScene();
    m_Scene->LoadContent();

    CheckForGLErrors();
}

void Game::StartGame() 
{ 
    delete m_Scene; 
    AudioManager::StopBGM();
    m_Scene = new GameScene();
    m_Scene->LoadContent();
}

void Game::MainMenu() 
{ 
    delete m_Scene;
    AudioManager::StopBGM();
    m_Scene = new MainMenuScene();
    m_Scene->LoadContent();
}

void Game::EndGame(uint aScore)
{
    delete m_Scene;
    AudioManager::StopBGM();
    m_Scene = new GameOverScene(aScore);
    m_Scene->LoadContent();
}

void Game::HandleInput(InputEvent& inputevent)
{
    m_Scene->HandleInput( inputevent );
}

void Game::Update(double aDelta)
{
    CheckForGLErrors();
    m_Scene->Update(aDelta);
    AudioManager::Update(aDelta);
	//update the damage post effect
	if (m_DamageEffectOn)
	{
		if (m_DamageEffectTimer >= DAMAGE_EFFECT_TIME)
		{
			TurnOffDamageEffect();
			m_DamageEffectTimer = 0.0;
		}
		m_DamageEffectTimer += aDelta;
	}
    CheckForGLErrors();
}

void Game::Draw()
{
    CheckForGLErrors();

    // clear the screen to gray.
	glClearColor(Colours::Gray.x, Colours::Gray.y, Colours::Gray.z, Colours::Gray.w);
	// bind our FBOD and setup the view port to the texture size
    GetFBOD()->Bind();
    glViewport(0, 0, g_pGame->GetFBOD()->m_TextureWidth, g_pGame->GetFBOD()->m_TextureHeight);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//draw scene to the FBOD
    m_Scene->Draw();
	// Unbind our FBOD and draw it to the back buffer and reset our view port
    GetFBOD()->Unbind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
	m_FrameBufferMesh->SetupAttributes(m_CurrentFBODShader);
	m_FrameBufferMesh->SetupUniforms(nullptr, m_CurrentFBODShader, 0, 0, 0, 0, GetTexture("PostEffect"), nullptr, Vector4(1, 1, 1, 1));
	m_FrameBufferMesh->Draw(m_CurrentFBODShader, nullptr);
    CheckForGLErrors();
}

void Game::Cleanup()
{
	Label::ClearFonts();
	AudioManager::ClearManager();
}


void Game::TurnOnDamageEffect()
{
	m_DamageEffectOn = true;
	m_DamageEffectTimer = 0.0;
}

void Game::TurnOffDamageEffect()
{
	m_DamageEffectOn = false;
}