#include "CommonHeader.h"

GameObject::GameObject()
{
    m_Scene = 0;

    m_Position.Set( 0, 0, 0 );
    m_Rotation.Set( 0, 0, 0 );
    m_Scale.Set( 0, 0, 0 );

    m_Mesh = 0;
    m_PhysicsBody = 0;

    m_ShaderProgram = 0;
    m_TextureHandle = 0;
}

GameObject::GameObject(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture, Material* aSecondaryTexture)
{
    m_Scene = 0;

    m_Position.Set( 0, 0, 0 );
    m_Rotation.Set( 0, 0, 0 );
    m_Scale.Set( 0, 0, 0 );

    m_Mesh = 0;
    m_PhysicsBody = 0;

    m_ShaderProgram = 0;
    m_TextureHandle = 0;

    Init(renderOrder,aScene, aName, aTag, aPosition, aRotation, aScale, aMesh, aShader, aTexture, aSecondaryTexture);
}

GameObject::~GameObject()
{
}

void GameObject::Init(unsigned int renderOrder,Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture, Material* aSecondaryTexture)
{
    m_Scene = aScene;

    m_Name = aName;
    m_Tag = aTag;

    m_Position = aPosition;
    m_Rotation = aRotation;
    m_Scale = aScale;

    m_Mesh = aMesh;

    m_ShaderProgram = aShader;
    m_TextureHandle = aTexture;
    m_SecondaryTextureHandle = aSecondaryTexture;

    m_RenderOrder = renderOrder;
}

void GameObject::UpdatePhysicsPosition()
{
    if (m_PhysicsBody != nullptr)
    {
        float angle = m_PhysicsBody->GetAngle();
        m_PhysicsBody->SetTransform(b2Vec2(m_Position.x, m_Position.y), angle);
    }
}

void GameObject::Update(double TimePassed)
{
    if( m_PhysicsBody )
    {
        b2Vec2 pos = m_PhysicsBody->GetPosition();
        float32 angle = -m_PhysicsBody->GetAngle() / PI * 180.0f;

        m_Position.x = pos.x;
        m_Position.y = pos.y;

        m_Rotation.z = angle;
    }
}

void GameObject::Draw(int renderorder)
{
    if( m_Mesh == 0 )
        return;

    if( m_RenderOrder == renderorder)
    {
        ShaderProgram* pShaderProgram = m_ShaderProgram;

        m_Matrix.CreateSRT(m_Scale, m_Rotation, m_Position);
		//getting the camera matrix (if the scene does not have one create identity)
		MyMatrix camMat;
		camMat.SetIdentity();
		if (m_Scene->GetCamera() != nullptr)
		{
			camMat = m_Scene->GetCameraMatrix();
		}

        MyMatrix normMat = m_Matrix;
        normMat.CreateSRT(Vector3(1, 1, 1), m_Rotation, m_Position);

        m_Mesh->SetupAttributes( pShaderProgram );
        m_Mesh->SetupUniforms(this,pShaderProgram, &m_Matrix, &camMat, &m_Scene->GetMatrix(), &normMat , m_TextureHandle, m_SecondaryTextureHandle, Vector4(1,1,1,1) );
        m_Mesh->Draw( pShaderProgram,this );
    }
}

void GameObject::AddPhysicsShape(b2Shape* shape, uint bodyType, bool isSensor)
{
    assert(m_PhysicsBody == 0);

    if( m_PhysicsBody == 0 )
    {
        b2BodyDef bodydef;
        bodydef.position.Set( m_Position.x, m_Position.y ); // bottom-left corner
        bodydef.angle = m_Rotation.z * PI / 180.0f;
        switch (bodyType)
        {
        case 0:
            bodydef.type = b2_staticBody;
            break;
        case 1:
            bodydef.type = b2_dynamicBody;
            break;
        case 2:
            bodydef.type = b2_kinematicBody;
        }

        m_PhysicsBody = m_Scene->GetBox2DWorld()->m_World->CreateBody( &bodydef );
        m_PhysicsBody->SetUserData( this );
    }

    b2FixtureDef fixturedef;
    fixturedef.shape = shape;
    fixturedef.density = 1;
    fixturedef.isSensor = isSensor;

    m_PhysicsBody->CreateFixture( &fixturedef );
}

void GameObject::AddPhysicsBox(vec2 size, uint bodyType, bool isSensor)
{
    b2PolygonShape boxshape;
    boxshape.SetAsBox( size.x/2, size.y/2 );

    AddPhysicsShape( &boxshape, bodyType, isSensor );
}

void GameObject::AddPhysicsChain(b2Vec2* pointlist, int numpoints)
{
    b2ChainShape chainshape;
    chainshape.CreateChain( pointlist, numpoints );

    AddPhysicsShape( &chainshape, false );
}

bool GameObject::SetFilterData(CollisionBits category, unsigned int mask, int groupIndex)
{
	if (m_PhysicsBody == 0)
	{
		return false;
	}

	b2Filter filterData = GetPhysicsBody()->GetFixtureList()->GetFilterData();
	filterData.categoryBits = category;
	filterData.maskBits = mask;
	filterData.groupIndex = groupIndex;
	GetPhysicsBody()->GetFixtureList()->SetFilterData(filterData);

	return true;
}
