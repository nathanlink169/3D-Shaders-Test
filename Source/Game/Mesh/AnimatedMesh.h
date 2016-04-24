#pragma once
#include "Mesh.h"

struct UserData
{
    int m_CurrentFrame = 0;
    float m_AnimationTime = 0.0f;
    std::string m_CurrentAnimation = "NONE";
};

struct AnimationData
{
    void Init(int* frames, int frameCount, float frameSpeed, bool doesLoop)
    {
        m_Frames = frames;
        m_FrameSpeed = frameSpeed;
        m_DoesLoop = doesLoop;
        m_NumberOfFrames = frameCount;
    }

    void UpdateAnimation(UserData* userData, double timePassed)
    {
        if (m_NumberOfFrames > 1)
        {
            userData->m_AnimationTime += (float)timePassed;
            if (userData->m_AnimationTime >= m_FrameSpeed)
            {
                userData->m_CurrentFrame++;
                if (userData->m_CurrentFrame > (m_NumberOfFrames - 1) && m_DoesLoop == true)
                    userData->m_CurrentFrame = 0;
                else if (m_DoesLoop == false)
                    userData->m_CurrentFrame = m_NumberOfFrames - 1;
                userData->m_AnimationTime = 0.0f;
            }
        }
    }

    int* m_Frames;
    int m_NumberOfFrames;
    bool m_DoesLoop;
    float m_FrameSpeed;
};
class AnimatedMesh :
    public Mesh
{
protected:
    std::map<std::string, AnimationData*> m_Animations;
    std::map<std::string, UserData*> m_Users;
    float m_FrameChangeX;
    float m_FrameChangeY;
    float m_FramesX;
    float m_FramesY;
public:
    AnimatedMesh();
    ~AnimatedMesh();

    void Init(float framesOnX, float framesOnY);

    void AddAnimation(std::string name, int* frames, int frameCount, float animationSpeed, bool doesLoop = true);
    void AddUser(GameObject* user);

    void SetUserAnimation(std::string userName, std::string newAnimationName);
    void SetUserFrame(std::string userName, int frame);

    void UpdateAnimationCycles(double timePassed);
    void Draw(ShaderProgram* pShaderProgram, GameObject* drawer);
};

