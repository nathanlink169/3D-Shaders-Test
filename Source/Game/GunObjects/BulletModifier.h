#ifndef __BulletModifier_H_
#define __BulletModifier_H_

/*
Bullet Modifier effects the bullets speed, as well as how the bullets position
should be changing based on it's base position (i.e. in a sin wave, in a circle)
*/

enum BulletModifierType
{
    BM_Sin = 0, 
	BM_Damage,
    BM_Speed, 
    BM_Fire,
    BM_Poison,
    BM_Freeze,
    BM_Circle,
    BM_AirMine,
    BM_Bouncy,
	BM_SuperSin,
    MAX_BULLET_MODIFIERS
};

class BulletModifier
{
public:
    BulletModifier(BulletModifierType aType, std::string aName);
    BulletModifier(BulletModifier* aModifier);
	virtual ~BulletModifier();

	virtual void Update(double aDelta) = 0;

	std::string GetName() { return m_Name; }

	Effect* GetEffect() { return m_Effect; }
	float GetAttackModifier() { return m_AttackModifier; }
	float GetSpeedModifier() { return m_SpeedModifier; }
	vec2 GetPositionOffset() { return m_PositionOffset; }

    BulletModifierType GetType() { return m_Type; }
protected:
	std::string m_Name;

	vec2 m_PositionOffset;
	Effect* m_Effect;
	float m_AttackModifier;
	float m_SpeedModifier;

    BulletModifierType m_Type;
};

#endif