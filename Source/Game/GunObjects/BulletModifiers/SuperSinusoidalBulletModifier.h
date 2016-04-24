#ifndef __SuperSinusoidalBulletModifier_H_
#define __SuperSinusoidalBulletModifier_H_

class SuperSinusoidalBulletModifier
    : public BulletModifier
{
public:
	SuperSinusoidalBulletModifier();
	SuperSinusoidalBulletModifier(BulletModifier* aModifier) : BulletModifier(aModifier), m_TimePassed(0) {}
	virtual ~SuperSinusoidalBulletModifier();

    void Update(double aDelta);
private:
    double m_TimePassed;
};

#endif