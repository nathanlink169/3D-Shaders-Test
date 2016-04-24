#include "CommonHeader.h"
#include "AnimatedMesh.h"


AnimatedMesh::AnimatedMesh() : Mesh()
{

}

void AnimatedMesh::Init(float framesOnX, float framesOnY)
{
	m_FramesX = framesOnX;
	m_FramesY = framesOnY;
	m_FrameChangeX = 1.0f / framesOnX;
	m_FrameChangeY = 1.0f / framesOnY;

}

AnimatedMesh::~AnimatedMesh()
{
	for each(auto iterator in m_Animations)
	{
		delete[] iterator.second->m_Frames;
		delete iterator.second;
	}
	for each(auto iterator in m_Users)
	{
		delete iterator.second;
	}
	m_Animations.clear();
	m_Users.clear();
}

void AnimatedMesh::AddAnimation(std::string name, int* frames,int frameCount, float animationSpeed, bool doesLoop)
{
	AnimationData* data = new AnimationData();
	data->Init(frames, frameCount, animationSpeed, doesLoop);
	m_Animations[name] = data;
}

void AnimatedMesh::AddUser(GameObject* user)
{
	UserData* data = new UserData();
	m_Users[user->GetName()] = data;
}

void AnimatedMesh::SetUserAnimation(std::string userName, std::string newAnimationName)
{
	m_Users[userName]->m_CurrentAnimation = newAnimationName;
	m_Users[userName]->m_CurrentFrame = 0;
	m_Users[userName]->m_AnimationTime = 0.0f;
}

void AnimatedMesh::SetUserFrame(std::string userName, int frame)
{
	m_Users[userName]->m_CurrentFrame = m_Animations[m_Users[userName]->m_CurrentAnimation]->m_Frames[frame];
	m_Users[userName]->m_AnimationTime = 0.0f;
}

void AnimatedMesh::UpdateAnimationCycles(double timePassed)
{
	for each(auto iterator in m_Users)
	{
		AnimationData* data = m_Animations[iterator.second->m_CurrentAnimation];
		data->UpdateAnimation(iterator.second,timePassed);
	}
}
void AnimatedMesh::Draw(ShaderProgram* pShaderProgram, GameObject* drawer)
{
    VertexFormat* verts = m_Verticies;
    int frame = m_Animations[m_Users[drawer->GetName()]->m_CurrentAnimation]->m_Frames[m_Users[drawer->GetName()]->m_CurrentFrame];

	float x, y;
	if (frame == 0)
	{
		y = 0.0f;
		x = 0.0f;
	}
	else
	{
		y = m_FrameChangeY * (int)(frame / m_FramesX);
		x = m_FrameChangeX * (int)(frame % (int)m_FramesX);
	}

	verts[0].uv.x = x;
	verts[0].uv.y = y - m_FrameChangeY;

	verts[1].uv.x = x;
	verts[1].uv.y = y;

	verts[2].uv.x = x + m_FrameChangeX;
	verts[2].uv.y = y;

	verts[3].uv.x = x + m_FrameChangeX;
	verts[3].uv.y = y - m_FrameChangeY;

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat)*m_VertAmount, m_Verticies, m_Usage);

	Mesh::Draw(pShaderProgram, drawer);
}