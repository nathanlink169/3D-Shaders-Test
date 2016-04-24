#ifndef __Mesh_H__
#define __Mesh_H__
const int LIGHT_EFFECTED_MAX = 6;
class GameObject;

struct Material
{
    Material(GLuint texture, float reflectAmount = 0.0f, float shineAmount = 0.0f)
    {
        TextureHandle = texture;
        ReflectAmount = reflectAmount;
        ShineAmount = shineAmount;
    }
    GLuint TextureHandle;
    float ReflectAmount;
    float ShineAmount;
};
class Mesh
{
protected:
    GLuint m_VBO;
    GLuint m_IBO;

    unsigned int m_NumVerts;
    unsigned int m_NumIndices;

    GLenum m_PrimitiveType;


	float m_Width;
	float m_Height;

    VertexFormat* m_Verticies;
    unsigned int* m_Indicies;

	bool m_OwnsData;

	int m_VertAmount;
	GLenum m_Usage;

public:
    Mesh();
    virtual ~Mesh();

	// V Width and Height - used by font system V //
	void SetWidth(float aWidth) { m_Width = aWidth; }
	void SetHeight(float aHeight) { m_Height = aHeight; }

	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }
	// ^ Width and Height - used by font system ^ //

	//Memory protection
	void SetOwnsData(bool too) { m_OwnsData = too; }
	bool OwnsData() { return m_OwnsData; }
	//-----------

    virtual void Init(VertexFormat* verts, int numverts, unsigned int* indices, int numindices, GLenum usage, GLenum primitivetype = GL_TRIANGLES);
	virtual void Init(const void* verts, int numverts, int vertexbytesize, GLenum usage, GLenum primitivetype = GL_TRIANGLES);

    virtual void SetupAttributes(ShaderProgram* pShaderProgram);
    virtual void SetupUniforms(GameObject* drawer, ShaderProgram* pShaderProgram, mat4* worldmat, mat4* camMat, mat4* projMat, mat4* normMat, Material* texturehandle, Material* secondaryTextureHandle, Vector4 color);
    virtual void Draw(ShaderProgram* pShaderProgram, GameObject* drawer);

    // defined in MeshShapes.cpp
	static Mesh* CreateBox(Vector2 size, bool isAnimated = false);
    //Marks Generation Methods
    static Mesh* GenerateTexturePlane(float width, float height, int vertCountX, int vertCountZ, int tileCountPerTextureX, int tileCountPerTextureZ);
    static Mesh* GenerateTextureBox(float size);
    static Mesh* GenerateTexturePlatform(float sizeX, float sizeY, float sizeZ);
	static Mesh* LoadOBJFile(const char* objfilename, Vector3 scale);
    static Mesh* GenerateSkyBox(float size);
    //Vert Generation Methods
    static VertexFormat* GenerateParticle(float size);
    //Nathans 
    static Mesh* GenerateFont(TTF::Font* aFont, float aScale, TTF::CodePoint aCodePoint);

    GLuint GetVBO() { return m_VBO; }
};

#endif //__Game_H__
