#ifndef __Gun_H_
#define __Gun_H_

/*
Each gun holds its own barrel modifer and bullet modifierS
-Barrel modifier changes the manner in which the bullets are spawned
	-How often
	-What direction they start
	-etc
-Bullet modifiers change the bullets themselves
	-Their position
	-Their speed
	-Any effects they have
*/

class Label;

class Gun
    : public GameObject
{
public:
    Gun(unsigned int renderOrder,GameScene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture);
	virtual ~Gun();

    void Update(double aDelta); 

    void InitializeModifiers(float aBaseChanceForModifiers);

    void Fire(vec2 aDirection);

	BarrelModifier* GetBarrelModifier() { return m_BarrelModifier; }

	std::string GetName() { return m_Name; }
private:
	BarrelModifier* m_BarrelModifier;
	std::vector <BulletModifier*> m_BulletModifiers;

	std::string m_Name;
};

#endif