#ifndef __PreloaderScene_H__
#define __PreloaderScene_H__

class Label;

enum PreloaderSteps
{
	LoadBase = 0,
	LoadShaders,
	LoadMeshes,
	LoadTextures,
    LoadFonts,
	LoadAudio,
	MAX_LOAD_STEPS
};

enum FontstoLoad
{
    ComicFont = 1,
    MAX_FONTS_TO_LOAD
};

enum ShadersToLoad
{
	TextureShader,
	SkyBoxShader,
	ReflectionShader,
	FadedTextureShader,
	OverlayedTextureShader,
	TwoDColourShader,
	MAX_SHADERS_TO_LOAD
};

enum TexturesToLoad
{
	MegamanTexture = 0,
	MegamanAnimatedTexture,
	PlayerArmTexture,
	WaterTexture,
	MetalTexture,
	GunTexture,
	BlackTexture,
	EnemyTexture,
    CubeMapTexture,
	ForceFieldTexture,
	ParticleTexture,
	MAX_TEXTURES_TO_LOAD
};

enum MeshesToLoad
{
	WaterMesh = 0,
	PlatformMesh,
    SkyBoxMesh,
	SphereMesh,
	CubeMesh,
	MAX_MESHES_TO_LOAD
};

enum AudioToLoad
{
	InitializeAudioManager,
	MAX_AUDIO_TO_LOAD
};

class PreloaderScene : public Scene
{
public:
	PreloaderScene();
	virtual ~PreloaderScene();

    virtual void OnSurfaceChanged(unsigned int aWidth, unsigned int aHeight);
    virtual void LoadContent();

    virtual void Update(double aDelta);
    virtual void Draw();

    virtual void CreateCameraObject();

    void UpdateLabels();
    void UpdateLabels(std::string aMainLabelString, std::string aDetailsLabelString);
private:
	void LoadBaseLabel();
	uint LoadGameShaders(uint aStep);
	uint LoadGameMeshes(uint aStep);
	uint LoadGameTextures(uint aStep);
	uint LoadGameAudio(uint aStep);
    uint LoadGameFonts(uint aStep);

	uint m_MajorStep;
	uint m_SubStep;

	Label* m_LoadingLabel;
    Label* m_DetailsLabel;
};

#endif //__Scene_H__
