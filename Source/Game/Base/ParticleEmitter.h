#pragma once
#include "GameObject.h"
struct PartcileGroup;
enum ParticleTypes
{
	SPAWN_PORTAL_PARTICLE,
	DESPAWN_PORTAL_PARTICLE,
	MAX_PARTICLE_TYPES
};
struct Particle
{
	void Init(VertexFormat* verts, float size, ParticleTypes type = DESPAWN_PORTAL_PARTICLE)
	{
		Verts = verts;
		m_Size = size;
		m_LocalPosition = Vector3(0, 0, 0);
		m_Position = Vector3(0, 0, 0);

		UpdateParticleType(type);
	}
	void DeleteMemory()
	{
		delete[] Verts;
	}
	void UpdateParticleType(ParticleTypes type)
	{
		float incrementAmount = 1.0f / MAX_PARTICLE_TYPES;
		Verts[0].uv.x = 0.0f + (incrementAmount * type);
		Verts[0].uv.y = 0.0f;

		Verts[1].uv.x = 0.0f + (incrementAmount * type);
		Verts[1].uv.y = 1.0f;

		Verts[2].uv.x = incrementAmount + (incrementAmount * type);
		Verts[2].uv.y = 1.0f;

		Verts[3].uv.x = incrementAmount + (incrementAmount * type);
		Verts[3].uv.y = 0.0f;
	}
	void SetPosition(Vector3 too) { m_Position = too; SetVertsRelativeToPos(); }
	void SetVertsRelativeToPos()
	{
		float halfSize = m_Size / 2.0f;

		Verts[0].pos.x = m_Position.x - halfSize;
		Verts[0].pos.y = m_Position.y - halfSize;

		Verts[1].pos.x = m_Position.x - halfSize;
		Verts[1].pos.y = m_Position.y + halfSize;

		Verts[2].pos.x = m_Position.x + halfSize;
		Verts[2].pos.y = m_Position.y + halfSize;

		Verts[3].pos.x = m_Position.x + halfSize;
		Verts[3].pos.y = m_Position.y - halfSize;
	}
	float m_Size;
	VertexFormat* Verts;
    Vector3 m_Position;
	Vector3 m_LocalPosition;
};

struct ParticleGroup;

class ParticleEmitter :
	public GameObject
{
protected:
	float m_ParticleSize;
	unsigned int m_GroupAmount;
	unsigned int m_ParticlesPerGroup;
	ParticleGroup* m_ParticleGroups;
public:
    ParticleEmitter(unsigned int renderOrder, ParticleTypes particleType, float particleSize, unsigned int numberOfGroups, unsigned int particlesPerGroup, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture);
	VertexFormat* AssembleParticleVerts();
	unsigned int* AssembleParticleInds();
	unsigned int GetNumberOfParticles() { return m_ParticlesPerGroup * m_GroupAmount; }
	void Update(double TimePassed);
	~ParticleEmitter();
};

struct ParticleGroup
{
	void Init(Particle* particles, int numberOfParticles, ParticleEmitter* emitter)
	{
		Particles = particles;
		NumberOfParticles = numberOfParticles;
		m_Emitter = emitter;
	}
	void DeleteMemory()
	{
		for (int i = 0; i < NumberOfParticles; i++)
		{
			Particles[i].DeleteMemory();
		}
		delete[] Particles;
	}
	void SetPositionRelativeToEmitter()
	{
		m_Position = m_Emitter->GetPosition() + m_LocalPosition;
		SetParticlesRelativeToMe();
	}
	void SetParticlePosRelativeToGroup(Particle* particle)
	{
		Vector3 RelativePos = m_Position + particle->m_LocalPosition;
		particle->SetPosition(RelativePos);
	}
	void SetLocalPosition(Vector3 too)
	{
		m_LocalPosition = too;
		SetPositionRelativeToEmitter();
	}
	void SetParticlesRelativeToMe()
	{
		for (int i = 0; i < NumberOfParticles; i++)
		{
			Particles[i].SetPosition(m_Position + Particles[i].m_LocalPosition);
		}
	}
	Particle* Particles;
	int NumberOfParticles;
	Vector3 m_MaxVelocity;
	Vector3 m_MinVelocity;
	Vector3 m_Position;
	Vector3 m_LocalPosition;
	ParticleEmitter* m_Emitter;
};