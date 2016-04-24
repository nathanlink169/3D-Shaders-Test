#include "CommonHeader.h"



ParticleEmitter::ParticleEmitter(unsigned int renderOrder, ParticleTypes particleType, float particleSize, unsigned int numberOfGroups, unsigned int particlesPerGroup,
    Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture)
    : GameObject(renderOrder, aScene, aName, aTag, aPosition, aRotation, aScale, aMesh, aShader, aTexture)
{
	m_ParticleSize = particleSize;
	m_GroupAmount = numberOfGroups;
	m_ParticlesPerGroup = particlesPerGroup;
	m_ParticleGroups = new ParticleGroup[numberOfGroups];
	for (unsigned int i = 0; i < numberOfGroups; i++)
	{
		ParticleGroup* group = new ParticleGroup();
		group->m_LocalPosition = Vector3(0, 0, 0);
		Particle* particles = new Particle[particlesPerGroup];
		for (unsigned int j = 0; j < particlesPerGroup; j ++)
		{
			particles[j].Init(Mesh::GenerateParticle(particleSize), particleSize, particleType);
		}
		group->Init(particles, particlesPerGroup, this);
		group->SetPositionRelativeToEmitter();
		m_ParticleGroups[i] = *group;
	}
}


ParticleEmitter::~ParticleEmitter()
{
	for (unsigned int i = 0; i < m_GroupAmount; i++)
	{
		m_ParticleGroups[i].DeleteMemory();
	}
	delete[] m_ParticleGroups;
}

VertexFormat* ParticleEmitter::AssembleParticleVerts()
{
	VertexFormat* verts = new VertexFormat[(m_GroupAmount * m_ParticlesPerGroup) * 4];
	int counter = 0;
	for (unsigned int i = 0; i < m_GroupAmount; i++)
	{
		for (unsigned int j = 0; j < m_ParticlesPerGroup; j++)
		{
			for (unsigned int k = 0; k < 4; k++)
			{
				verts[counter] = m_ParticleGroups[i].Particles[j].Verts[k];
				counter++;
			}
		}
	}
	return verts;
}

unsigned int* ParticleEmitter::AssembleParticleInds()
{
	unsigned int* inds = new unsigned int[(m_GroupAmount * m_ParticlesPerGroup) * 6];
	int counter = 0;
	int counter2 = 0;
	for (unsigned int i = 0; i < m_GroupAmount; i++)
	{
		for (unsigned int j = 0; j < m_ParticlesPerGroup; j++)
		{
			inds[counter + 0] = counter2 + 0;
			inds[counter + 1] = counter2 + 1;
			inds[counter + 2] = counter2 + 2;
			inds[counter + 3] = counter2 + 0;
			inds[counter + 4] = counter2 + 2;
			inds[counter + 5] = counter2 + 3;

			counter += 6;
			counter2 += 4;
		}
	}
	return inds;
}

void ParticleEmitter::Update(double timePassed)
{

}