#pragma once
#include "GameObject.h"
class Gun;
class PickUp : public GameObject
{
protected:
    bool m_FlagForReset;
public:
	PickUp() {}
    PickUp(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture);
    ~PickUp();
    void OnBeginContact(b2Contact* contact);
    void Update(double TimePassed);
	void ReturnPickUp();
};

