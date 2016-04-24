#ifndef __CameraObject_H__
#define __CameraObject_H__

class CameraObject : public GameObject
{
protected:

public:
    CameraObject();
    CameraObject(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture);
    virtual ~CameraObject();

    virtual void Update(double TimePassed);
    void Reset();
};

#endif //__CameraObject_H__
