#ifndef __GameScene_H__
#define __GameScene_H__

//constants
const float  CAMERA_PERSPECTIVE_ANGLE = 45.0f;
const float CAMERA_ASPECT_RATIO = 1.0f;
const float CAMERA_NEAR_Z = 0.01f;
const float CAMERA_FAR_Z = 1130.0f;
const float CAMERA_MAX_2D_DIST = 0.5f;

const int GAME_ROCK_COUNT = 50;
const float ROCK_SPAWN_TIME = 1.0f;

const int WATER_RIPPLE_ACTIVE_DEFAULT = 0;
const float WATER_RIPPLE_RADIUS_MAX_DEFAULT = 0.0f;
const float WATER_RIPPLE_SIZE_MAX = 55.0f;
const float WATER_RIPPLE_SIZE_GROWTH_RATE = 5.0f;
const float WATER_RIPPLE_RADIUS_MIN_DEFAULT = -20.0f;
const float WATER_RIPPLE_SIN_TIME_DEFAULT = -1.0f;
const float WATER_RIPPLE_DECAY_DEFAULT = 5.0f;
const float WATER_RIPPLE_DECAY_RATE = 25.0f;

class Bullet;
class HUD;

class GameScene : public Scene
{
private:
    void LoadGameObjects();
    void CreateCameraObject();
	void LoadAnimatedMeshes();
	void LoadParticleMeshes();

    void CreateGround(Vector3 aPosition, Vector3 aScale, Mesh* aMesh, Material* aTexture);
    int m_GroundCount; // Do not remove

    void RepoolObjects();

	HUD* m_HUD;
	ParticleMesh* m_ParticleMesh;
	Mesh* m_SkyBoxMesh;
	bool m_DrawB2dDebug;

protected:
    ContactListener* m_ContactListener;

    Pool<Bullet>* m_Bullets;
    std::vector<Bullet*> m_RepoolBullets;

    Pool<EnemyObject>* m_Enemies;
    std::vector<EnemyObject*> m_RepoolEnemies;

	//pickup related variables
	Pool<PickUp>* m_PickUps;
	std::vector<PickUp*> m_RepoolPickups;
	std::vector<Vector3> m_SpawnPickupLocs;

    float m_EnemySpawnRate;
    float m_EnemySpawnTimer;

    //Water Ripple Variables
    Vector3 RipplePos[GAME_ROCK_COUNT];
    int RippleActive[GAME_ROCK_COUNT];
    float RippleDecay[GAME_ROCK_COUNT];
    float RippleMaxRadius[GAME_ROCK_COUNT];
    float RippleMinRadius[GAME_ROCK_COUNT];
    float RippleSinTime[GAME_ROCK_COUNT];

	int m_MaxScore;
	int m_Score;

public:
    GameScene();
    virtual ~GameScene();

    virtual void OnSurfaceChanged(unsigned int aWidth, unsigned int aHeight);
    virtual void LoadContent();

    virtual void Update(double aDelta);
    virtual void Draw();

    //getters for the ripple variables
    Vector3* GetRipplePos() { return RipplePos; }
    int* GetRippleActive() { return RippleActive; }
    float* GetRippleDecay() { return RippleDecay; }
    float* GetRippleMaxRadius() { return RippleMaxRadius; }
    float* GetRippleMinRadius() { return RippleMinRadius; }
    float* GetRippleSinTime() { return RippleSinTime; }

    Bullet* GetBullet() { return m_Bullets->GetNew(); }
    void ReturnBullet(Bullet* aBullet) { m_RepoolBullets.push_back(aBullet); }

    EnemyObject* GetEnemy() { return m_Enemies->GetNew(); }
    void ReturnEnemy(EnemyObject* aEnemy) { 
		aEnemy->GetPhysicsBody()->SetActive(false);
		aEnemy->SetPosition(Vector3(0, 200, 0));
		m_RepoolEnemies.push_back(aEnemy); 
	}

	void ReturnPickup(PickUp* aPickUp) {
		aPickUp->GetPhysicsBody()->SetActive(false);
		aPickUp->SetPosition(Vector3(0, 200, 0));
		m_RepoolPickups.push_back(aPickUp); 
	}

	void SpawnPickUp(EnemyObject* aSpawner);

	PlayerObject* GetPlayer() { return (PlayerObject*)(m_GameObjects["Player"]); }

	void AddToScore(int points) { m_Score += points; if (m_Score >= m_MaxScore) m_MaxScore = m_Score; }
	void SetScore(int aScore) { m_Score = aScore; if (m_Score >= m_MaxScore) m_MaxScore = m_Score; }
	int GetScore() { return m_Score; }
	int GetMaxScore() { return m_MaxScore; }
};

#endif //__Scene_H__
