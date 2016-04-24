#ifndef __PoisonBulletModifer_H_
#define __PoisonBulletModifer_H_

class PoisonBulletModifer
    : public BulletModifier
{
public:
    PoisonBulletModifer();
    PoisonBulletModifer(BulletModifier* aModifier) : BulletModifier(aModifier) {}
    virtual ~PoisonBulletModifer();

    void Update(double aDelta) {}

private:
};

#endif