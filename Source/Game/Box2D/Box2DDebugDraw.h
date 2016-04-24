#ifndef __Box2DDebugDraw_H__
#define __Box2DDebugDraw_H__

class Box2DDebugDraw : public b2Draw
{
public:
	Mesh* m_pMesh;

	ShaderProgram* m_pShaderProgram;

	Scene* m_pScene;
	MyMatrix* m_pMatProj;

public:
	Box2DDebugDraw(ShaderProgram* pShaderProgram);
	~Box2DDebugDraw();

	virtual void Draw(const b2Vec2* vertices, int32 vertexCount, const b2Color& color, unsigned char alpha, int primitivetype);
	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color); // CCW order.
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color); // CCW order.
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	virtual void DrawTransform(const b2Transform& xf);

	void SetProjMatrix(MyMatrix* pMatProj) { m_pMatProj = pMatProj; }
	void SetScene(Scene* pScene) { m_pScene = pScene; }
};

#endif //__Box2DDebugDraw_H__
