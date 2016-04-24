#ifndef __Font_H__
#define __Font_H__

enum LabelOrientation
{
    Left, Center, Right
};

class Label : public GameObject
{
public:
    Label(Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture) : Text(""), Colour(vec4(1, 1, 1, 1)), Orientation(Left) { Init(0,aScene, aName, aTag, aPosition, aRotation, aScale, aMesh, aShader, aTexture, nullptr); }
    Label(Scene* aScene, std::string aName, std::string aTag, Vector3 aPosition, Vector3 aRotation, Vector3 aScale, Mesh* aMesh, ShaderProgram* aShader, Material* aTexture, std::string aText, vec4 aColour) : Text(aText), Colour(aColour), Orientation(Left) { Init(0,aScene, aName, aTag, aPosition, aRotation, aScale, aMesh, aShader, aTexture, nullptr); }
	~Label(){}

	std::string Text;
	vec4 Colour;
    LabelOrientation Orientation;

	// Setters
	void SetFont(std::string aFont) { m_Font = aFont; }

	// Getters
	std::string GetFont() { return m_Font; }
private:
	std::string m_Font;
	static std::map<std::string, std::map<uint, Mesh*>> s_Meshes;

    static std::string m_CurrentFontLoading;
    static uint m_CurrentCodePoint;
    static std::mutex m_CodePointMutex;
    static std::mutex m_MapMutex;
public:
	static void ClearFonts()
	{
		for each(auto iterator in s_Meshes)
			npw::SafeDeleteMap(s_Meshes[iterator.first]); 
	}

	static void LoadFont(std::string aFont)
	{
        if (DRAW_TEXT == false)
            return;

		// If the font already exists in the map, don't load anything.
		if (!(s_Meshes.find(aFont) == s_Meshes.end()))
			return;

        TTF::Font* font = new TTF::Font("Data/Fonts/" + aFont + ".ttf");

		for (uint i = 33; i < 128; i++)
		{
            s_Meshes[aFont][i] = Mesh::GenerateFont(font, 1, TTF::CodePoint(i));
			if (s_Meshes[aFont][i] == nullptr)
				s_Meshes[aFont].erase(i);
		}
	}

	// Inherited from GameObject
	void Draw(int renderorder)
	{
        if (DRAW_TEXT == false)
            return;

		if (Text.empty())
			return;

		unsigned int index = Text[0];
		Mesh* mesh = s_Meshes[m_Font][index];

		if (m_RenderOrder == renderorder)
		{
			ShaderProgram* pShaderProgram = m_ShaderProgram;
            vec3 pos = m_Position;
            
            switch (Orientation)
            {
            case Center:
                pos.x -= GetTotalWidth() / 2.0f;
                break;
            case Right:
                pos.x -= GetTotalWidth();
                break;
            }

			m_Matrix.CreateSRT(m_Scale, m_Rotation, pos);
			//getting the camera matrix (if the scene does not have one create identity)
			MyMatrix camMat;
			camMat.SetIdentity();
			if (m_Scene->GetCamera() != nullptr)
			{
				camMat = m_Scene->GetCameraMatrix();
			}

			for (uint i = 0; i < Text.size(); i++)
			{
				if (Text[i] == ' ')
				{
					m_Matrix.Translate(GetScale().x, 0, 0);
					continue;
				}
                MyMatrix normMat = m_Matrix;
                normMat.CreateSRT(Vector3(1, 1, 1), m_Rotation, pos);

				s_Meshes[m_Font][Text[i]]->SetupAttributes(pShaderProgram);
                s_Meshes[m_Font][Text[i]]->SetupUniforms(this, pShaderProgram, &m_Matrix, &camMat, &m_Scene->GetMatrix(), &normMat, m_TextureHandle, nullptr, Colour);
				s_Meshes[m_Font][Text[i]]->Draw(pShaderProgram, this);

				float width = s_Meshes[m_Font][Text[i]]->GetWidth();
				float height = s_Meshes[m_Font][Text[i]]->GetHeight();
				m_Matrix.Translate(width * 1.1f * GetScale().x, 0.0f, 0.0f);
			}
		}
	}

    float GetTotalWidth()
    {
        float width = 0;
        for (uint i = 0; i < Text.size(); i++)
        {
            if (Text[i] == ' ')
                width += GetScale().x;
            else
                width += s_Meshes[m_Font][Text[i]]->GetWidth() * 1.1f * GetScale().x;
            
        }
        return width;
    }
};

#endif