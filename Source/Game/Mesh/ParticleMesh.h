#pragma once
#include "Mesh.h"
#include "Game/Base/ParticleEmitter.h"
struct Emitter
{
	ParticleEmitter* m_Emitter;
	unsigned int m_ParticleCount;
	VertexFormat* m_Verts;
	unsigned int* m_Inds;

	Emitter(ParticleEmitter* emitter)
	{
		m_Emitter = emitter;

		m_Verts = m_Emitter->AssembleParticleVerts();
		m_Inds = m_Emitter->AssembleParticleInds();

		m_ParticleCount = m_Emitter->GetNumberOfParticles();
	}
	void CleanUpData()
	{
		if (m_Verts != nullptr)
		{
			delete[] m_Verts;
			m_Verts = nullptr;
		}
		if (m_Inds != nullptr)
		{
			delete[] m_Inds;
			m_Inds = nullptr;
		}
	}
	void AssembleVerts() { m_Verts = m_Emitter->AssembleParticleVerts();}
	void AssembleInds() { m_Inds = m_Emitter->AssembleParticleInds(); }
};

class ParticleMesh :
	public Mesh
{
protected:
	std::map<std::string, Emitter*> m_Emitters;
public:
	ParticleMesh();
	~ParticleMesh();
	void AssembleParticleEmitterData();
	unsigned int GetNumberOfParticles();
	void AddEmitter(ParticleEmitter* emitter);
};

