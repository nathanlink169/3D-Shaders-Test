#ifndef __SinBulletModifier_H_
#define __SinBulletModifier_H_

class SinBulletModifier
    : public BulletModifier
{
public:
    SinBulletModifier();
    SinBulletModifier(BulletModifier* aModifier) : BulletModifier(aModifier) , m_TimePassed(0) {}
    virtual ~SinBulletModifier();

    void Update(double aDelta);
private:
    double m_TimePassed;
};

#endif