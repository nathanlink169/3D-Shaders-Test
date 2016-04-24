#include "CommonHeader.h"  

ChainLink::ChainLink(Scene* pScene, std::string name, Vector3 pos, Vector3 rot, Vector3 scale, Mesh* pMesh, ShaderProgram* pShader, GLuint texture)
    : m_NextLink(nullptr)
{
    Init(pScene, name, pos, rot, scale, pMesh, pShader, texture);

    AddPhysicsBox(vec2(scale.x, scale.y), 1);
    
    b2MassData data;
    GetPhysicsBody()->GetMassData(&data);
    data.mass = 0.1;
    GetPhysicsBody()->SetMassData(&data);
    pScene->AddGameObject(this, name);
}

ChainLink* ChainLink::SetNextLink(ChainLink* aNextLink)
{ 
    m_NextLink = aNextLink; 

    b2RevoluteJointDef jointDef;

    b2Body* thisBody = GetPhysicsBody();
    b2Body* nextBody = aNextLink->GetPhysicsBody();

    vec2 pos = npw::MidpointBetweenPoints(thisBody->GetPosition().x, thisBody->GetPosition().y, nextBody->GetPosition().x, nextBody->GetPosition().y);
    b2Vec2 b2pos = b2Vec2(pos.x, pos.y);

    jointDef.Initialize(thisBody, nextBody, b2Vec2(GetPosition().x, GetPosition().y));

    m_pScene->GetBox2DWorld()->m_pWorld->CreateJoint(&jointDef);

    return aNextLink; 
}