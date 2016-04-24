#ifndef __AssaultRifleBarrelModifier_H_
#define __AssaultRifleBarrelModifier_H_

class AssaultRifleBarrelModifier
	: public BarrelModifier
{
public:
    AssaultRifleBarrelModifier(GameScene* aScene);
    virtual ~AssaultRifleBarrelModifier();

    virtual std::vector<Bullet*> Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers);
private:
};

#endif