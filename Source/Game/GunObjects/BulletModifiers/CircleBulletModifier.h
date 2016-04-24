#ifndef __CircleBulletModifier_H_
#define __CircleBulletModifier_H_

class CircleBulletModifier
    : public BulletModifier
{
public:
    CircleBulletModifier();
    CircleBulletModifier(BulletModifier* aModifier) : BulletModifier(aModifier), m_TimePassed(0) {}
    virtual ~CircleBulletModifier();

    void Update(double aDelta);

private:
    double m_TimePassed;
};

#endif