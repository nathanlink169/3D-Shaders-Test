#ifndef __ScoreDisplay_H_
#define __ScoreDisplay_H_

class Label;

class ScoreDisplay :
	public GameObject
{
public:
	ScoreDisplay();
    ScoreDisplay(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale);
	~ScoreDisplay();

	void Draw(int aRenderOrder);

	void SetPreText(std::string aText) { m_PreText = aText; }
	void SetPostText(std::string aText) { m_PostText = aText; }

	void SetScore(long long score) { m_Score = score; }
    long long GetScore() { return m_Score; }
private:
	Label* m_Label;
	std::string m_PreText;
	std::string m_PostText;

    long long m_Score;
};

#endif