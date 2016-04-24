#ifndef __BarrelModifier_H_
#define __BarrelModifier_H_

/*
Barrel Modifier is a class template, and each subclass controls how the bullets are spawned.

NOTE: Barrel modifiers do not hold their own Bullet Modifiers. The gun holds its own bullet modifiers,
generated randomly on the guns spawn.
*/

const float BASE_TIME_BETWEEN_SHOTS = 0.5f;

class Bullet;
class BulletModifier;

class BarrelModifier
{
public:
    BarrelModifier(GameScene* aScene, std::string aName) : m_Scene(aScene), m_Name(aName), m_MaxShotTime(BASE_TIME_BETWEEN_SHOTS), m_CurrentShotTime(0) {}
	virtual ~BarrelModifier();

    void Update(double aDelta);

    virtual std::vector<Bullet*> Shoot(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers);

    GameScene* GetGameScene() { return m_Scene; }
	std::string GetName() { return m_Name; }
protected:
	std::string m_Name;
    virtual std::vector<Bullet*> Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers) = 0;
    GameScene* m_Scene;
    float m_CurrentShotTime;
    float m_MaxShotTime;
};

#endif