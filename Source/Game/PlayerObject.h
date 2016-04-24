#ifndef __PlayerObject_H__
#define __PlayerObject_H__

class Gun;

enum PlayerState
{
    IDLE = 0,
    RUN,
    JUMP,
    SHOOT
};
enum Direction
{
	LEFT = 0,
	RIGHT
};

class PlayerObject : public GameObject
{
protected:
	const float PLAYER_MOVE_SPEED = 6.0f;
	const float PLAYER_JUMP_SPEED = 9.8f;

    PlayerState m_CurrentState;
	Direction m_Direction;
	bool m_UpdateAnimation;

	int m_NumFootContacts;

    vec3 m_InitialPosition;
    vec3 m_InitialRotation;

	GameObject* m_Arm;

    Gun* m_Gun;
    vec2 m_GunAngle;

public:
    PlayerObject();
    PlayerObject(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture);
    virtual ~PlayerObject();

	void CreateFootSensor();

    virtual void Update(double TimePassed);
    virtual void Draw(int renderorder);

    void UpdateGun(double TimePassed);
	void UpdateAnimation();

    void SetGun();

    void Reset();

    bool CanJump() { return true; }

    void OnBeginContact(b2Contact* contact);
    void OnEndContact(b2Contact* contact);

	Gun* GetGun() { return m_Gun; }
};

#endif //__PlayerObject_H__
