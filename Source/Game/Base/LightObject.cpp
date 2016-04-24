#include "CommonHeader.h"
#include "LightObject.h"


LightObject::LightObject()
{
}

LightObject::LightObject(unsigned int renderOrder, Vector4 aLightColor, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture)
    : GameObject(renderOrder, aScene, aName, aTag, aPosition, aRotation, aScale, aMesh, aShader, aTexture)
    , m_LightColor(aLightColor)
{
}

LightObject::~LightObject()
{
}
