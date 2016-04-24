#include "CommonHeader.h"


PickUp::PickUp(unsigned int renderOrder,Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture)
{
    Init(renderOrder, aScene, aName, aTag, aPosition, aRotation, aScale, aMesh, aShader, aTexture);
    m_FlagForReset = false;
    AddPhysicsBox(vec2(1.0f, 1.0f), 1, false);
    GetPhysicsBody()->GetFixtureList()->SetFriction(0);
	GetPhysicsBody()->SetActive(false);

    SetFilterData(ITEM, PLAYER | BLOCKS);
}

void PickUp::Update(double TimePassed)
{
	GameObject::Update(TimePassed);
    if (m_FlagForReset)
    {
        GetPhysicsBody()->SetActive(false);
        SetPosition(Vector3(0, 300, 0));
		ReturnPickUp();
        m_FlagForReset = false;
    }
}

void PickUp::ReturnPickUp()
{
	GameScene* pTest = (GameScene*)m_Scene;
	pTest->ReturnPickup(this);
}

PickUp::~PickUp()
{
}

void PickUp::OnBeginContact(b2Contact* contact)
{
    GameObject* object = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
    if (object != nullptr)
    {
        if (object->GetTag() == "Player")
        {
            PlayerObject* player = (PlayerObject*)contact->GetFixtureA()->GetBody()->GetUserData();
            m_FlagForReset = true;

			GameScene* gameScene = (GameScene*)m_Scene;
			gameScene->AddToScore(200);

			player->SetGun();
        }
    }
}