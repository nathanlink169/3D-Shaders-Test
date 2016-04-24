#ifndef __Bullet_H_
#define __Bullet_H_

/*
These are the game objects that will get pooled.
Whenever something needs to spawn a bullet, Initialize() should be called.

When the bullet collides with a game object, you can get the attack power, 
and any effects that should be applied to the game object, through getters.

Bullets hold their own pointers to modifiers, and many bullets with hold
pointers to the same modifier (i.e. the same point in memory).
*/

class Effect;

const float BULLET_BASE_ATTACK_POWER = 5.0f;
const float BULLET_BASE_ATTACK_SPEED = 0.1f;
const float BULLET_LIFETIME = 5.0f;

class Bullet
    : public GameObject
{
public:
    Bullet() {}
    Bullet(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture);
	virtual ~Bullet();

    void Update(double TimePassed);

    void SetModifiers(std::vector<BulletModifier*> aModifiers);

	void Initialize(vec2 aPosition, vec2 aVelocity, std::vector<BulletModifier*> aModifiers); // Velocity will be a normalized vector
	vec2 GetPositionOffset();

	void ReturnToPool();

	std::vector<Effect*> GetEffects(bool copy = true);
	float GetAttackPower();
	float GetAttackSpeed();

    void Reset();

private:
    //Pool<Bullet>* m_Pool;
    
	std::vector<BulletModifier*> m_Modifiers;
    vec2 m_BasePosition;
    vec2 m_Velocity;

    float m_TimeRemaining = BULLET_LIFETIME;

    
};

#endif