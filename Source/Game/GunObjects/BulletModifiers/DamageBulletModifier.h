#ifndef __DamageBulletModifier_H_
#define __DamageBulletModifier_H_

class DamageBulletModifier
    : public BulletModifier
{
public:
	DamageBulletModifier();
	DamageBulletModifier(BulletModifier* aModifier) : BulletModifier(aModifier) {}
	virtual ~DamageBulletModifier();

    void Update(double aDelta) {}

private:
};

#endif