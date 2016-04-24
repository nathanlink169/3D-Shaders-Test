#ifndef __HUD_H__
#define __HUD_H__

class HUD
{
public:
	HUD(Scene* pScene, Vector3 scale, Gun* aGun);
	virtual ~HUD();

    void Update(double TimePassed);
	void Draw();

	ScoreDisplay* GetScoreDisplay() { return m_ScoreDisplay; }
private:
	Gun* m_Gun;
	Label* m_WeaponLabel;
	ScoreDisplay* m_ScoreDisplay;
};

#endif //__CameraObject_H__
