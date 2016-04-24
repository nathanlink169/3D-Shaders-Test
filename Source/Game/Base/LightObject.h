#pragma once
#include "GameObject.h"
class LightObject :
    public GameObject
{
protected:
    Vector4 m_LightColor;
public:
    LightObject();
    LightObject(unsigned int renderOrder, Vector4 aLightColor, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture);
    ~LightObject();
    Vector4 GetLightColor() { return m_LightColor; }
};

