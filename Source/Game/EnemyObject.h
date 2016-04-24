#ifndef __EnemyObject_H__
#define __EnemyObject_H__

class Effect;

const float ENEMY_START_HEALTH = 50.0f;

class EnemyObject
    : public GameObject
{
public:
	const double ENEMY_SPAWN_PICKUP_RATE = 0.1;
protected:
	const float MOVE_SPEED = 3.0f;
	const float JUMP_SPEED = 10.0f;

	float m_Health;

    char m_Direction;

	std::vector<Effect*> m_Effects;
	float GetSpeedModifier();
	float GetPoisonRate();

	bool m_FlagForDespawn; 

    vec3 m_InitialPosition;
    vec3 m_InitialRotation;

    Pool<EnemyObject*> m_Pool;

public:
    EnemyObject();
    EnemyObject(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture);
    virtual ~EnemyObject();

    virtual void Update(double TimePassed);
    virtual void Draw(int renderorder);

	void SetHealth(float aHealth) { m_Health = aHealth; }

    void Reset();

    void OnBeginContact(b2Contact* contact);
    void OnEndContact(b2Contact* contact);

    void ReturnToPool();

    void AddEffect(Effect* effect);

    void UpdateEffects();
};

#endif //__PlayerObject_H__
