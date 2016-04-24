#include "CommonHeader.h"

BulletModifier::BulletModifier(BulletModifierType aType, std::string aName)
    : m_Type(aType) 
    , m_AttackModifier(1)
    , m_Effect(nullptr)
    , m_PositionOffset(vec2(0, 0))
    , m_SpeedModifier(1)
	, m_Name(aName)
{
} 

BulletModifier::~BulletModifier()
{
    npw::SafeDelete(m_Effect);
}

BulletModifier::BulletModifier(BulletModifier* aModifier)
{
    this->m_AttackModifier = aModifier->m_AttackModifier;
    if (aModifier->m_Effect != nullptr)
        this->m_Effect = new Effect(*(aModifier->m_Effect));
    else
        this->m_Effect = nullptr;
    this->m_PositionOffset = aModifier->m_PositionOffset;
    this->m_SpeedModifier = aModifier->m_SpeedModifier;
    this->m_Type = aModifier->m_Type;
	this->m_Name = aModifier->m_Name;
}