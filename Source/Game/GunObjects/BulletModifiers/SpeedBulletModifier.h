#ifndef __SpeedBulletModifier_H_
#define __SpeedBulletModifier_H_

class SpeedBulletModifier
    : public BulletModifier
{
public:
    SpeedBulletModifier();
    SpeedBulletModifier(BulletModifier* aModifier) : BulletModifier(aModifier) {}
    virtual ~SpeedBulletModifier();

    void Update(double aDelta) {}

private:
};

#endif