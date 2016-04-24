#include "CommonHeader.h"

#include "Box2DDebugDraw.h"

Box2DDebugDraw::Box2DDebugDraw(ShaderProgram* pShaderProgram)
{
    m_pShaderProgram = pShaderProgram;

    m_pMesh = new Mesh();

	m_pScene = nullptr;
}

Box2DDebugDraw::~Box2DDebugDraw()
{
    delete m_pMesh;
}

void Box2DDebugDraw::Draw(const b2Vec2* vertices, int32 vertexCount, const b2Color& color, unsigned char alpha, int primitivetype)
{
    m_pMesh->Init( vertices, vertexCount, sizeof(float)*2*vertexCount, GL_DYNAMIC_DRAW, primitivetype );

    // bind our vertex and index buffers.
    glBindBuffer( GL_ARRAY_BUFFER, m_pMesh->GetVBO() );

    // setup the position attribute.
    GLint aPos = glGetAttribLocation( m_pShaderProgram->GetProgram(), "a_Position" );
    assert( aPos != -1 );
    glVertexAttribPointer( aPos, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (void*)0 );
    glEnableVertexAttribArray( aPos );

    MyMatrix matworld;
    matworld.SetIdentity();

	MyMatrix matcam = m_pScene->GetCameraMatrix();

    Vector4 color4( color.r, color.g, color.b, alpha/255.0f );

	m_pMesh->SetupUniforms(nullptr, m_pShaderProgram, &matworld, &matcam, m_pMatProj, &matworld, nullptr, nullptr, color4);

    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );

    //glLineWidth( 1 );
    m_pMesh->Draw( m_pShaderProgram,nullptr );

    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
}

void Box2DDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    Draw( vertices, vertexCount, color, 255, GL_LINE_LOOP );
}

void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    Draw( vertices, vertexCount, color, 128, GL_TRIANGLE_FAN );
    Draw( vertices, vertexCount, color, 255, GL_LINE_LOOP );
}

void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    static const int vertexCount = 24;
    float anglechange = 2.0f * PI / vertexCount;
	
    b2Vec2 vertices[vertexCount];
    for( int i=0; i<vertexCount; i++ )
    {
        vertices[i].x = center.x + cos( i*anglechange ) * radius;
        vertices[i].y = center.y + sin( i*anglechange ) * radius;
    }
	
    Draw( vertices, vertexCount, color, 128, GL_TRIANGLE_FAN );
}

void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    static const int vertexCount = 24;
    float anglechange = 2.0f * PI / vertexCount;
	
    b2Vec2 vertices[vertexCount];
    for( int i=0; i<vertexCount; i++ )
    {
        vertices[i].x = center.x + cos( i*anglechange ) * radius;
        vertices[i].y = center.y + sin( i*anglechange ) * radius;
    }
	
    Draw( vertices, vertexCount, color, 128, GL_TRIANGLE_FAN );
    Draw( vertices, vertexCount, color, 255, GL_LINE_LOOP );
}

void Box2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    b2Vec2 vertices[2] = { p1, p2 };

    Draw( vertices, 2, color, 255, GL_LINES );
}

void Box2DDebugDraw::DrawTransform(const b2Transform& xf)
{
    b2Vec2 vertices[2] = { xf.p };

    vertices[1] = xf.p + 0.5f * xf.q.GetXAxis();
    Draw( vertices, 2, b2Color( 1, 0, 0 ), 255, GL_LINES );

    vertices[1] = xf.p + 0.5f * xf.q.GetYAxis();
    Draw( vertices, 2, b2Color( 0, 1, 0 ), 255, GL_LINES );
}
