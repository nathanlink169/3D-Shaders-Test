#include "CommonHeader.h"

MainMenuScene::MainMenuScene()
{
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::OnSurfaceChanged(unsigned int aWidth, unsigned int aHeight)
{
    Scene::OnSurfaceChanged(aWidth, aHeight);
}

void MainMenuScene::LoadContent()
{
    Scene::LoadContent();

    CreateCameraObject(); 
	Label* label = new Label(this, "Loading Label", "Loading", vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.035f, 0.035f, 0.035f), nullptr, g_pGame->GetShader("2D Colour"), g_pGame->GetTexture("Black"));
    label->Colour = Colours::Crimson;
    label->SetFont("arial");
    label->Text = "Press Space To Start";
    label->Orientation = Center;
    AddGameObject(label, "Label");
    
	//AudioManager::PlayBGM("Main Theme");

	std::ifstream myfile("Data/SaveData/Score.npwscore");

	if (myfile.is_open())
	{
		std::string line;
		ScoreEntry entries;
		getline(myfile, line);
		entries.Name = line;
		getline(myfile, line);
		entries.Score = (uint)(std::stoi(line));

		Label* score = new Label(this, "High Score Label", "Label", vec3(0.0f, -0.1f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.015f, 0.015f, 0.015f), nullptr, g_pGame->GetShader("2D Colour"), g_pGame->GetTexture("Black"));
		score->Colour = Colours::Crimson;
		score->SetFont("arial");
		score->Text = "Highscore: " + entries.Name + " - " + std::to_string(entries.Score);
		score->Orientation = Center;
		AddGameObject(score, "HighScoreLabel");
	}
}

void MainMenuScene::Update(double aDelta)
{
    Scene::Update(aDelta);
    
    if (Input::KeyJustPressed(VK_SPACE))
        g_pGame->StartGame();


}

void MainMenuScene::Draw()
{
    m_Matrix.CreatePerspectiveVFoV(CAMERA_PERSPECTIVE_ANGLE, CAMERA_ASPECT_RATIO, CAMERA_NEAR_Z, CAMERA_FAR_Z);
    m_MainCamera->CreateLookAtLeftHandAndReturn(Vector3(0, 1, 0), GetGameObject("Label")->GetPosition());
    Scene::Draw();
}
