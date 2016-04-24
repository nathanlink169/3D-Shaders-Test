#include "CommonHeader.h"

#include "Box2DWorld.h"
#include "Box2DDebugDraw.h"

Box2DWorld::Box2DWorld(ShaderProgram* debugdrawshader)
{
    m_World = 0;
    m_DebugDraw = 0;
    m_UnusedTime = 0;

    CreateWorld( debugdrawshader );
}

Box2DWorld::~Box2DWorld()
{
    Cleanup();
}

void Box2DWorld::CreateWorld(ShaderProgram* debugdrawshader)
{
    m_World = new b2World( b2Vec2( 0, -10 ) );

    // Setup debug draw object.
    { 
        m_DebugDraw = new Box2DDebugDraw( debugdrawshader );
        m_World->SetDebugDraw( m_DebugDraw );

        uint32 flags = b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_centerOfMassBit | b2Draw::e_aabbBit | b2Draw::e_pairBit;
        m_DebugDraw->SetFlags( flags );
    }
}

void Box2DWorld::Update(double TimePassed)
{
  //  m_World->Step( TimePassed, 8, 3 );
    //m_World->Step(TimePassed, 8, 3);

    m_UnusedTime += (float)TimePassed;

    while( m_UnusedTime > 1/120.0f )
    {
        m_World->Step( 1.0f/120.0f, 8, 3 );
        m_UnusedTime -= 1/120.0f;
    }
}

void Box2DWorld::Cleanup()
{
    SAFE_DELETE( m_World );
    SAFE_DELETE( m_DebugDraw );
}
