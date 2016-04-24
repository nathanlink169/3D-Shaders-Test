#ifndef __AirMineBulletModifier_H_
#define __AirMineBulletModifier_H_

class AirMineBulletModifier
    : public BulletModifier
{
public:
    AirMineBulletModifier();
    AirMineBulletModifier(BulletModifier* aModifier) : BulletModifier(aModifier) {}
    virtual ~AirMineBulletModifier();

    void Update(double aDelta) {}

private:
};

#endif