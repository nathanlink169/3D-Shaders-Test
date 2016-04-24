#ifndef __Box2DWorld_H__
#define __Box2DWorld_H__

class Box2DWorld;
class Box2DDebugDraw;
class MaterialDefinition;

class Box2DWorld
{
public:
    b2World* m_World;
    Box2DDebugDraw* m_DebugDraw;

    float m_UnusedTime;

public:
    Box2DWorld(ShaderProgram* debugdrawshader);
    ~Box2DWorld();

    void CreateWorld(ShaderProgram* debugdrawshader);
    void Update(double TimePassed);
    void Cleanup();

    void SetContactListener(ContactListener* aContactListener) { m_World->SetContactListener(aContactListener); }
};

#endif //__Box2DWorld_H__
