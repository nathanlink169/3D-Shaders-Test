#ifndef __Game_H__
#define __Game_H__

class Game;

extern Game* g_pGame;

class ShaderProgram;

const double DAMAGE_EFFECT_TIME = 0.5;

class Game
{
protected:
    Scene* m_Scene;

    std::map<std::string, Mesh*> m_Meshes;
    std::map<std::string, ShaderProgram*> m_Shaders;
    std::map<std::string, Material*> m_Textures;

    unsigned int m_WindowWidth;
    unsigned int m_WindowHeight;

	Mesh* m_FrameBufferMesh;

    FBODefinition* m_FBOD;

	bool m_DamageEffectOn;
	double m_DamageEffectTimer;
	ShaderProgram* m_CurrentFBODShader;

public:
    Game();
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void HandleInput(InputEvent& inputevent);
    virtual void Update(double aDelta);
    virtual void Draw();

	void Cleanup();

    void StartGame();
    void MainMenu();
    void EndGame(uint aScore);

	void TurnOnDamageEffect();
	void TurnOffDamageEffect();
	bool IsDamageEffectOn(){ return m_DamageEffectOn; }
	void SetCurrentFBODShader(ShaderProgram* too) { m_CurrentFBODShader = too; }

    void AddMesh(const char* aName, Mesh* aMesh) { m_Meshes[aName] = aMesh; }
    void AddShader(const char* aName, ShaderProgram* aShader) { m_Shaders[aName] = aShader; }
    void AddTexture(const char* aName, Material* aMaterial) { m_Textures[aName] = aMaterial; }

    Mesh* GetMesh(const char* aName) { return m_Meshes[aName]; }
    ShaderProgram* GetShader(const char* aName) { return m_Shaders[aName]; }
    Material* GetTexture(const char* aName) { return m_Textures[aName]; }

    unsigned int GetWindowWidth() { return m_WindowWidth; }
    unsigned int GetWindowHeight() { return m_WindowHeight; }

    Scene* GetScene() { return m_Scene; }

    FBODefinition* GetFBOD() { return m_FBOD; }


};

#endif //__Game_H__
