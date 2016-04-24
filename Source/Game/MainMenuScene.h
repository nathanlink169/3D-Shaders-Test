#ifndef __MainMenuScene_H__
#define __MainMenuScene_H__

class MainMenuScene : public Scene
{
public:
    MainMenuScene();
    virtual ~MainMenuScene();

    virtual void OnSurfaceChanged(unsigned int aWidth, unsigned int aHeight);
    virtual void LoadContent();

    virtual void Update(double aDelta);
    virtual void Draw();
};

#endif //__Scene_H__
