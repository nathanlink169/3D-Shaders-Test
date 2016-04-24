#ifndef __SawedOffShotgunBarrelModifier_H_
#define __SawedOffShotgun BarrelModifier_H_

class SawedOffShotgunBarrelModifier
	: public BarrelModifier
{
public:
    SawedOffShotgunBarrelModifier(GameScene* aScene, uint aNumberOfBullets);
    virtual ~SawedOffShotgunBarrelModifier();

    virtual std::vector<Bullet*> Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers);
private:
    uint m_NumberOfBullets;
};

#endif