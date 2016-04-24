#ifndef __Scene_H__
#define __Scene_H__

class LightObject;

class Scene
{
protected:
    std::map<std::string, GameObject*> m_GameObjects;
    std::map<std::string, LightObject*> m_LightObjects;

    Box2DWorld* m_Box2DWorld;
	
	MyMatrix m_Matrix; // Projection Matrix. Do not remove.
    CameraObject* m_MainCamera;
    int m_LightCount; // Do not remove

public:
    Scene();
    virtual ~Scene();

    virtual void OnSurfaceChanged(unsigned int aWidth, unsigned int aHeight);
    virtual void LoadContent();

    virtual void HandleInput(InputEvent& aInputevent);
    virtual void Update(double aDelta);
    virtual void Draw();
    virtual void CreateCameraObject();
    void CreateLight(Vector3 aPosition, Vector4 aColour);

    CameraObject* GetCamera() { return m_MainCamera; }
    MyMatrix GetCameraMatrix() { return m_MainCamera->GetMatrix(); }


public:
    GameObject* GetGameObject(const char* aName) { return m_GameObjects[aName]; }
    Box2DWorld* GetBox2DWorld() { return m_Box2DWorld; }

	//ease of action functions
	MyMatrix GetMatrix() { return m_Matrix; }
	MyMatrix CreatePerspectiveVFOVAndReturn(float halfvertfovdegrees, float aspect, float nearZ, float farZ) { m_Matrix.CreatePerspectiveVFoV(halfvertfovdegrees, aspect, nearZ, farZ); return m_Matrix; }
	MyMatrix CreateOrthoAndReturn(float left, float right, float top, float bottom, float nearZ, float farZ) { m_Matrix.CreateOrtho(left, right, bottom, top, nearZ, farZ); return m_Matrix; }
    
    std::map<std::string, LightObject*> GetLights() { return m_LightObjects; }

    void AddGameObject(GameObject* aGameObject, std::string aName, bool isLight = false)
    { 
        (isLight) ? m_LightObjects[aName] = (LightObject*)aGameObject : nullptr;
        m_GameObjects[aName] = aGameObject; 
    }

    void RemoveGameObject(GameObject* aGameObject) { m_GameObjects.erase(aGameObject->GetName()); }
};

#endif //__Scene_H__
