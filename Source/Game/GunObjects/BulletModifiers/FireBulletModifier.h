#ifndef __FireBulletModifier_H_
#define __FireBulletModifier_H_

class FireBulletModifier
    : public BulletModifier
{
public:
    FireBulletModifier();
    FireBulletModifier(BulletModifier* aModifier) : BulletModifier(aModifier) {}
    virtual ~FireBulletModifier();

    void Update(double aDelta) {}

private:
};

#endif