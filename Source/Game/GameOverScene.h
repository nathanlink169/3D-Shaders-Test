#ifndef __GameOverScene_H__
#define __GameOverScene_H__

struct ScoreEntry
{
    ScoreEntry() { Name = ""; Score = 0; }
    std::string Name;
    uint Score;
};

class GameOverScene 
    : public Scene
{
public:
    GameOverScene(uint aScore);
    virtual ~GameOverScene();

    virtual void OnSurfaceChanged(unsigned int aWidth, unsigned int aHeight);
    virtual void LoadContent();

    virtual void Update(double aDelta);
    virtual void Draw();
private:
    std::string m_CurrentName;
    uint m_Characters;

    uint m_Score;
};

#endif //__Scene_H__
