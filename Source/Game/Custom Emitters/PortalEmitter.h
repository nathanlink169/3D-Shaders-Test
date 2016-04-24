#pragma once
#include "Game/Base/ParticleEmitter.h"
class PortalEmitter :
	public ParticleEmitter
{
public:
    PortalEmitter(unsigned int renderOrder,ParticleTypes particleType, float particleSize, unsigned int numberOfGroups, unsigned int particlesPerGroup,
		Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture);
	~PortalEmitter();
	void Update(double TimePassed);
};

