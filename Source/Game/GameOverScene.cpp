#include "CommonHeader.h"

GameOverScene::GameOverScene(uint aScore)
    : m_Score(aScore)
    , m_Characters(0)
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::OnSurfaceChanged(unsigned int aWidth, unsigned int aHeight)
{
    Scene::OnSurfaceChanged(aWidth, aHeight);
}

void GameOverScene::LoadContent()
{
    Scene::LoadContent();

    std::string line;
    std::ifstream myfile("Data/SaveData/Score.npwscore");

    ScoreEntry entries;
    bool onLeaderboard = false;

    if (myfile.is_open())
    {
		getline(myfile, line);
        entries.Name = line;
        getline(myfile, line);
        entries.Score = (uint)(std::stoi(line));
    }
    else
        onLeaderboard = true;

    if (m_Score > entries.Score)
        onLeaderboard = true;

    if (!onLeaderboard)
        g_pGame->MainMenu();

    else
    {
		AddGameObject(new Label(this, "TextLabel", "Label", vec3(-0.4f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.01f, 0.01f, 0.01f), nullptr, g_pGame->GetShader("2D Colour"), nullptr), "TextLabel");
        ((Label*)(m_GameObjects["TextLabel"]))->Orientation = Left;
        ((Label*)(m_GameObjects["TextLabel"]))->Colour = Colours::Crimson;
        ((Label*)(m_GameObjects["TextLabel"]))->SetFont("arial");
        ((Label*)(m_GameObjects["TextLabel"]))->Text = "New Highscore! Enter Name - ";

        CreateCameraObject();
    }
}

void GameOverScene::Update(double aDelta)
{
    Scene::Update(aDelta);

	if (Input::KeyJustPressed(VK_BACK))
	{
		if (m_CurrentName.size() > 0)
			m_CurrentName.pop_back();
		((Label*)(m_GameObjects["TextLabel"]))->Text = "New Highscore! Enter Name - " + m_CurrentName;
	}

	std::vector<uchar> keys = Input::KeysJustPressed();
	if (keys.size() > 0)
	{
		// Loop through all typeable keys
		for (uchar i = 32; i < 126; i++)
		{
			std::vector<uchar>::iterator it;

			it = std::find(keys.begin(), keys.end(), i);
			if (it != keys.end())
			{
				if (m_CurrentName.size() < 32)
				{
					if (Input::KeyIsPressed(VK_SHIFT) || i < 65 || i > 90)
						m_CurrentName.push_back(i);
					else
						m_CurrentName.push_back(i + 32);
				}
			}
		}
		((Label*)(m_GameObjects["TextLabel"]))->Text = "New Highscore! Enter Name - " + m_CurrentName;
	}

	if (Input::KeyJustPressed(VK_RETURN))
	{
		remove("Data/SaveData/Score.npwscore");

		std::ofstream myfile("Data/SaveData/Score.npwscore");
		myfile << m_CurrentName << std::endl << std::to_string(m_Score);
		myfile.close();
		g_pGame->MainMenu();
	}
}

void GameOverScene::Draw()
{
	m_Matrix.CreatePerspectiveVFoV(CAMERA_PERSPECTIVE_ANGLE, CAMERA_ASPECT_RATIO, CAMERA_NEAR_Z, CAMERA_FAR_Z);
	m_MainCamera->CreateLookAtLeftHandAndReturn(Vector3(0, 1, 0), GetGameObject("TextLabel")->GetPosition());
    Scene::Draw();
}