#ifndef __SMGBarrelModifier_H_
#define __SMGBarrelModifier_H_

class SMGBarrelModifier
	: public BarrelModifier
{
public:
    SMGBarrelModifier(GameScene* aScene);
    virtual ~SMGBarrelModifier();

	virtual std::vector<Bullet*> Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers);
private:
};

#endif