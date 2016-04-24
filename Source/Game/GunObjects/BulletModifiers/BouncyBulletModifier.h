#ifndef __BouncyBulletModifier_H_
#define __BouncyBulletModifier_H_

class BouncyBulletModifier
    : public BulletModifier
{
public:
    BouncyBulletModifier();
    BouncyBulletModifier(BulletModifier* aModifier) : BulletModifier(aModifier), m_TimePassed(0) {}
    virtual ~BouncyBulletModifier();

    void Update(double aDelta);
private:
    double m_TimePassed;
};

#endif