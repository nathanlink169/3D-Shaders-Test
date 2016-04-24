#include "CommonHeader.h"


PortalEmitter::PortalEmitter(unsigned int renderOrder, ParticleTypes particleType, float particleSize, unsigned int numberOfGroups, unsigned int particlesPerGroup,
	Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture)
	: ParticleEmitter(renderOrder,particleType,particleSize,numberOfGroups,particlesPerGroup,aScene,aName,aTag,aPosition,aRotation,aScale,aMesh,aShader,aTexture)
{
	for (unsigned int i = 0; i < m_GroupAmount; i++)
	{
		for (unsigned int j = 0; j < m_ParticlesPerGroup; j++)
		{
			float posX = (float)npw::Random() * 0.2f;
			float negX = (float)npw::Random() * 0.2f;
			float posY = (float)npw::Random() * 0.2f;
			float negY = (float)npw::Random() * 0.2f;

			m_ParticleGroups[i].Particles[j].m_LocalPosition.x = posX - negX;
			m_ParticleGroups[i].Particles[j].m_LocalPosition.y = posY - negY;
		}

		float posX = (float)npw::Random() * 3.0f;
		float negX = (float)npw::Random() * 3.0f;
		float posY = (float)npw::Random() * 3.0f;
		float negY = (float)npw::Random() * 3.0f;

		m_ParticleGroups[i].SetLocalPosition(Vector3(posX - negX, posY - negY, 0.0f));
		m_ParticleGroups[i].SetParticlesRelativeToMe();

		m_ParticleGroups[i].m_MaxVelocity = (m_Position - m_ParticleGroups[i].m_Position);
		m_ParticleGroups[i].m_MaxVelocity.Normalize();
	}
}


PortalEmitter::~PortalEmitter()
{
}

void PortalEmitter::Update(double TimePassed)
{
	for (unsigned int i = 0; i < m_GroupAmount; i++)
	{
		m_ParticleGroups[i].SetLocalPosition(m_ParticleGroups[i].m_LocalPosition + (m_ParticleGroups[i].m_MaxVelocity * (float)TimePassed));
		if (npw::DistanceBetweenPoints(m_ParticleGroups[i].m_Position, m_Position) <= 0.1f)
		{
			float posX = (float)npw::Random() * 2.0f;
			float negX = (float)npw::Random() * 2.0f;
			float posY = (float)npw::Random() * 2.0f;
			float negY = (float)npw::Random() * 2.0f;

			m_ParticleGroups[i].SetLocalPosition(Vector3(posX - negX, posY - negY, 0.0f));
			m_ParticleGroups[i].SetParticlesRelativeToMe();

			m_ParticleGroups[i].m_MaxVelocity = (m_Position - m_ParticleGroups[i].m_Position);
			m_ParticleGroups[i].m_MaxVelocity.Normalize();
		}
	}
}