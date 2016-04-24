#ifndef __Effect_H_
#define __Effect_H_
enum DamageType
{
    FIRE,
    POISION,
    NOTHING
};
class Effect
{
public:
    Effect(float aLifeSpan, float aPoisonRate = 0.0f, float aSpeedModifier = 1.0f, DamageType type = NOTHING)
        : m_LifeSpan(aLifeSpan)
        , m_TimeRemaining(aLifeSpan)
        , m_Poison(aPoisonRate)
        , m_Speed(aSpeedModifier)
        , m_DamageType(type){}

	Effect(Effect* aEffect)
		: m_LifeSpan(aEffect->m_LifeSpan)
		, m_TimeRemaining(aEffect->m_TimeRemaining)
		, m_Poison(aEffect->m_Poison)
		, m_Speed(aEffect->m_Speed)
        , m_DamageType(aEffect->m_DamageType){}
	
	virtual ~Effect();

	float GetPoisonRate() { return m_Poison; }
	float GetSpeedModifier() { return m_Speed; }
    float GetLifeSpan() { return m_LifeSpan; }
    float GetTimeRemaining() { return m_TimeRemaining; }
	void ReduceTime(float aTime) { m_TimeRemaining -= aTime; }
    DamageType GetDamageType() { return m_DamageType; }
private:
	float m_Poison; // How much health the object applied with this effect loses per second
	float m_Speed;  // How much faster the object applied with this effect moves
    float m_LifeSpan; // The Lifespan of the effect once it 
    float m_TimeRemaining; // The amount of time left
    DamageType m_DamageType; // Enum for effect graphics
};

#endif