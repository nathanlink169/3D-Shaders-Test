#ifndef __BaseBarrelModifier_H_
#define __BaseBarrelModifier_H_

class PistolBarrelModifier
    : public BarrelModifier
{
public:
    PistolBarrelModifier(GameScene* aScene);
    virtual ~PistolBarrelModifier();

	virtual std::vector<Bullet*> Shoot(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers);
    virtual std::vector<Bullet*> Fire(vec2 aPosition, vec2 aDirection, std::vector<BulletModifier*> aBulletModifiers);
};

#endif