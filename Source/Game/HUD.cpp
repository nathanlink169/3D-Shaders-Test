#include "CommonHeader.h"

HUD::HUD(Scene* pScene, Vector3 scale, Gun* aGun)
	: m_Gun(aGun) 
{ 
	m_WeaponLabel = new Label(pScene, "HUD Weapon Label", "Label", vec3(0.41f, -0.35f, 0.0f), vec3(0.0f, 0.0f, 0.0f), scale, nullptr, g_pGame->GetShader("2D Colour"), nullptr);
	m_WeaponLabel->Orientation = Right;
	m_WeaponLabel->SetFont("arial");
	m_WeaponLabel->Colour = Colours::Orange;
	m_ScoreDisplay = new ScoreDisplay(0,pScene, "HUD Score Display", "Score Display", vec3(-0.41f, 0.35f, 0.0f), vec3(0.0f, 0.0f, 0.0f), scale * 1.5f);

	m_ScoreDisplay->SetPreText("Score: ");
}

HUD::~HUD()
{
}

void HUD::Update(double TimePassed)
{
	m_WeaponLabel->Text = m_Gun->GetName();
}

void HUD::Draw()
{
	for (uint i = 0; i < 5; i++)
	{
		m_WeaponLabel->Draw(i);
		m_ScoreDisplay->Draw(i);
	}
}