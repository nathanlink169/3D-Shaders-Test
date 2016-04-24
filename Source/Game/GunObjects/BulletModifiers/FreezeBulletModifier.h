#ifndef __FreezeBulletModifer_H_
#define __FreezeBulletModifer_H_

class FreezeBulletModifer
    : public BulletModifier
{
public:
    FreezeBulletModifer();
    FreezeBulletModifer(BulletModifier* aModifier) : BulletModifier(aModifier) {}
    virtual ~FreezeBulletModifer();

    void Update(double aDelta) {}

private:
};

#endif