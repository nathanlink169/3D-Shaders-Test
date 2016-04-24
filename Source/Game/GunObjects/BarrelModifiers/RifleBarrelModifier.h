#ifndef __RifleBarrelModifier_H_
#define __RifleBarrelModifier_H_

class RifleBarrelModifier
	: public BarrelModifier
{
public:
    RifleBarrelModifier(GameScene* aScene);
    virtual ~RifleBarrelModifier();

	virtual std::vector<Bullet*> Shoot(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers);
    virtual std::vector<Bullet*> Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers);
private:
};

#endif