#ifndef __GameObject_H__
#define __GameObject_H__

class ShaderProgram;
class Mesh;
class Scene;

enum CollisionBits
{
    PLAYER = 0x0001,
    ENEMY =  0x0002,
    BULLET = 0x0004,
    BLOCKS = 0x0008,
    ITEM =   0x0010,
    EXIT =   0x0020
};

class GameObject
{

protected:
    Scene* m_Scene;

    std::string m_Name;
    std::string m_Tag;

    Vector3 m_Position;
    Vector3 m_Rotation;
    Vector3 m_Scale;

    Mesh* m_Mesh;
    b2Body* m_PhysicsBody;

    ShaderProgram* m_ShaderProgram;
    Material* m_TextureHandle;
    Material* m_SecondaryTextureHandle;

    MyMatrix m_Matrix;

    unsigned int m_RenderOrder;

    void AddPhysicsShape(b2Shape* aShape, uint aBodyType, bool aIsSensor = false);
    void UpdatePhysicsPosition();


public:
    GameObject();
    GameObject(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture, Material* aSecondaryTexture = nullptr);
    virtual ~GameObject();

    virtual void Init(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture, Material* aSecondaryTexture = nullptr);

    virtual void Update(double aDelta);
    virtual void Draw(int aRenderOrder);

    void AddPhysicsBox(vec2 aSize, uint aBodyType, bool aIsSensor = false);
    void AddPhysicsChain(b2Vec2* aPointList, int aNumberOfPoints);

	bool SetFilterData(CollisionBits aCategory, unsigned int aMask, int aGroupIndex = 0);

    b2Body* GetPhysicsBody() { return m_PhysicsBody; }

    virtual void OnBeginContact(b2Contact* aContact) {}
    virtual void OnEndContact(b2Contact* aContact) {}

public:
    void SetMesh(Mesh* aMesh) { m_Mesh = aMesh; }
    void SetShader(ShaderProgram* aShader) { m_ShaderProgram = aShader; }
    void SetTexture(Material* aTextureHandle) { m_TextureHandle = aTextureHandle; }

    Mesh* GetMesh() { return m_Mesh; }
    ShaderProgram* GetShader() { return m_ShaderProgram; }
    Material* GetTexture() { return m_TextureHandle; }

    void SetPosition(Vector3 aPosition) { m_Position = aPosition; UpdatePhysicsPosition(); }
    void SetRotation(Vector3 aRotation) { m_Rotation = aRotation; UpdatePhysicsPosition(); }
    void SetScale(Vector3 aScale) { m_Scale = aScale; UpdatePhysicsPosition(); }

	//ease of access functions, can return matrix after performing various creates
	MyMatrix GetMatrix() { return m_Matrix; }
	MyMatrix CreateSRTAndReturn() { m_Matrix.CreateSRT(m_Scale, m_Rotation, m_Position); return m_Matrix; }
    MyMatrix CreateNormSRTAndReturn() { m_Matrix.CreateSRT(Vector3(1, 1, 1), m_Rotation, m_Position); return m_Matrix; }
	MyMatrix CreateLookAtLeftHandAndReturn(Vector3 up, Vector3 targetPos) { m_Matrix.CreateLookAtViewLeftHanded(m_Position, up, targetPos); return m_Matrix; }

    Vector3 GetPosition() { return m_Position; }
    Vector3 GetRotation() { return m_Rotation; }
    Vector3 GetScale()  { return m_Scale; }

	vec2 GetVelocity() { return npw::b2Vec2_To_vec2(m_PhysicsBody->GetLinearVelocity()); }
    Scene* GetScene() { return m_Scene; }

    virtual void Reset() {}
    std::string GetName() { return m_Name; }
    std::string GetTag() { return m_Tag; }
};

#endif //__GameObject_H__
