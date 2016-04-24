#include "CommonHeader.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    for each( auto iterator in m_GameObjects )
        delete iterator.second;
}

void Scene::OnSurfaceChanged(unsigned int aWidth, unsigned int aHeight)
{
}

void Scene::LoadContent()
{
    g_pGame->AddShader( "Box2DDebugShader", new ShaderProgram( "Data/Shaders/Box2DDebug.vert", "Data/Shaders/Box2DDebug.frag" ) );

    m_Box2DWorld = new Box2DWorld( g_pGame->GetShader( "Box2DDebugShader" ));
}

void Scene::CreateCameraObject()
{
     m_MainCamera = new CameraObject(0,this, "Camera", "Camera", Vector3(0, 3, -12), Vector3(0, 0, 0), Vector3(1, 1, 1), nullptr, nullptr, nullptr);
}

void Scene::HandleInput(InputEvent& aInputevent)
{
}

void Scene::Update(double aDelta)
{
    CheckForGLErrors();

    m_Box2DWorld->Update(aDelta);

    // update all of the Scene objects in the list.
    for each( auto iterator in m_GameObjects )
    {
        iterator.second->Update(aDelta);
    }

    CheckForGLErrors();
}

void Scene::Draw()
{
    CheckForGLErrors();

    // render all of the Scene objects in the list.
    for( int i=0; i<5; i++ )
    {
        for each( auto iterator in m_GameObjects )
        {
            iterator.second->Draw( i );
        }
    }

 
    CheckForGLErrors();
}

void Scene::CreateLight(Vector3 aPosition, Vector4 aColour)
{
    if (DRAW_LIGHTS)
    {
        AddGameObject(new LightObject(0, aColour, this, "Light" + std::to_string(m_LightCount), "Light", aPosition, vec3(0, 0, 0), vec3(1, 1, 1), nullptr, nullptr, nullptr), "Light" + std::to_string(m_LightCount), true);
        m_LightCount++;
    }
}