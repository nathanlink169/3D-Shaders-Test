#include "CommonHeader.h"


ParticleMesh::ParticleMesh() : Mesh()
{
	m_OwnsData = false;
}


ParticleMesh::~ParticleMesh()
{
}

void ParticleMesh::AddEmitter(ParticleEmitter* TheEmitter)
{
	Emitter* emitter = new Emitter(TheEmitter);
	m_Emitters[TheEmitter->GetName()] = emitter;
}

void ParticleMesh::AssembleParticleEmitterData()
{
	int numberOfVerts = 0;
	int numberOfInds = 0;

	for each(auto iterator in m_Emitters)
	{
		numberOfVerts += iterator.second->m_ParticleCount * 4;
		numberOfInds += iterator.second->m_ParticleCount * 6;
	}

	VertexFormat* verts = new VertexFormat[numberOfVerts];
	unsigned int* inds = new unsigned int[numberOfInds];

	int currentNumberOfParticles = 0;
	for each(auto iterator in m_Emitters)
	{
		iterator.second->AssembleInds();
		iterator.second->AssembleVerts();
		for (unsigned int i = 0; i < iterator.second->m_ParticleCount * 4; i++)
		{
		
			verts[i + (currentNumberOfParticles * 4)] = iterator.second->m_Verts[i];
			int ind = iterator.second->m_Inds[i] + (currentNumberOfParticles * 6);
			inds[i + (currentNumberOfParticles * 6)] = ind;
		}
		iterator.second->CleanUpData();
		currentNumberOfParticles += iterator.second->m_ParticleCount;
	}

	Init(verts, numberOfVerts, inds, numberOfInds, GL_STATIC_DRAW, GL_TRIANGLES);

	delete[] verts;
	delete[] inds;
}