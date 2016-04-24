#include "CommonHeader.h"


ScoreDisplay::ScoreDisplay()
{
    m_Score = 0;
	m_Label = nullptr;
}
ScoreDisplay::ScoreDisplay(unsigned int renderOrder, Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale)
    : GameObject(renderOrder, aScene, aName, aTag, aPosition, aRotation, aScale, nullptr, nullptr, nullptr)
	, m_Score(0)
{
	m_Label = new Label(aScene, "Score Display Text", "Label", aPosition, aRotation, aScale, nullptr, g_pGame->GetShader("2D Colour"), nullptr);
	m_Label->Orientation = Left;
	m_Label->SetFont("arial");
	m_Label->Colour = Colours::Orange;
}

ScoreDisplay::~ScoreDisplay()
{
}

void ScoreDisplay::Draw(int aRenderOrder)
{
	m_Label->Text = m_PreText + std::to_string(m_Score) + m_PostText;
	m_Label->Draw(aRenderOrder);
}