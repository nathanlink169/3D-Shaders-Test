#include "CommonHeader.h"

CameraObject::CameraObject()
{
}

CameraObject::CameraObject(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture)
{
    Init(renderOrder, aScene, aName, aTag, aPosition, aRotation, aScale, aMesh, aShader, aTexture);
}

CameraObject::~CameraObject()
{
}

void CameraObject::Reset()
{
    PlayerObject* player = ((PlayerObject*)(m_Scene->GetGameObject("Player")));

    Vector3 pos = player->GetPosition();
    pos.z = GetPosition().z;

    SetPosition(pos);
}

void CameraObject::Update(double TimePassed)
{
    GameObject::Update(TimePassed);

    PlayerObject* player = ((PlayerObject*)(m_Scene->GetGameObject("Player")));

    Vector3 pos = player->GetPosition();
    pos.z = GetPosition().z;

	//keep the camera near the player
	float dist = (float)npw::DistanceBetweenPoints(GetPosition().x, GetPosition().y, player->GetPosition().x, player->GetPosition().y);
	if (dist > CAMERA_MAX_2D_DIST)
	{
	    float x = player->GetPosition().x - GetPosition().x;
	    float y = player->GetPosition().y - GetPosition().y;
	    float angle = atan2(y, x);
	    float distDifference = dist - CAMERA_MAX_2D_DIST;
	    Vector3 posChange = Vector3(GetPosition().x + cos(angle) * distDifference, GetPosition().y + sin(angle) * distDifference, GetPosition().z);

	    /*if (posChange.x < GetPosition().x)
	    posChange.x = GetPosition().x;*/

	    SetPosition(posChange);
	}

    // PLayer Follow Camera, Needs to be implemented in a new camera object as 
    // this class is now a generic camera that will be used for still menus

    //update camera / control camera
    /* NOTE Matrix GetAt,GetRight ect are Right Handed while we are working in left handed
    that is why move.x and move.y have - before them*/

    /*if (g_KeyStates['I'])
    {
        Vector3 move = GetMatrix().GetAt() * (5 * TimePassed);
        SetPosition(GetPosition() + Vector3(-move.x, -move.y, move.z));
    }
    if (g_KeyStates['K'])
    {
        Vector3 move = GetMatrix().GetAt() * (5 * TimePassed);
        SetPosition(GetPosition() - Vector3(-move.x, -move.y, move.z));
    }
    if (g_KeyStates['J'])
    {
        Vector3 move = GetMatrix().GetRight() * (5 * TimePassed);
        SetPosition(GetPosition() + Vector3(-move.x, -move.y, move.z));
    }
    if (g_KeyStates['L'])
    {
        Vector3 move = GetMatrix().GetRight() * (5 * TimePassed);
        SetPosition(GetPosition() - Vector3(-move.x, -move.y, move.z));
    }
    if (g_KeyStates['U'])
    {
        SetPosition(GetPosition() + Vector3(0.0f, 5 * TimePassed, 0.0f));
    }
    if (g_KeyStates['O'])
    {
        SetPosition(GetPosition() - Vector3(0.0f, 5 * TimePassed, 0.0f));
    }*/

 
}
