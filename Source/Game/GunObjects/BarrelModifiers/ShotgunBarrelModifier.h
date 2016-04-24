#ifndef __ShotgunBarrelModifier_H_
#define __ShotgunBarrelModifier_H_

class ShotgunBarrelModifier
	: public BarrelModifier
{
public:
    ShotgunBarrelModifier(GameScene* aScene, uint aNumberOfBullets);
    virtual ~ShotgunBarrelModifier();

    virtual std::vector<Bullet*> Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers);
private:
    uint m_NumberOfBullets;
};

#endif