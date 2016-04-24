#include "CommonHeader.h"

Mesh::Mesh()
{
	m_VBO = 0;
	m_IBO = 0;
	m_PrimitiveType = GL_TRIANGLES;
	m_Verticies = nullptr;
	m_Indicies = nullptr;
	m_OwnsData = true;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	if (m_Verticies != nullptr && m_OwnsData)
		delete[] m_Verticies;
	if (m_Indicies != nullptr && m_OwnsData)
		delete[] m_Indicies;
}

void Mesh::Init(VertexFormat* verts, int numverts, unsigned int* indices, int numindices, GLenum usage, GLenum primitivetype)
{
	m_NumVerts = numverts;
	m_NumIndices = numindices;

	// gen and fill buffer with our vertex attributes.
	if (m_VBO == 0)
		glGenBuffers(1, &m_VBO);
	if (m_Verticies != nullptr && m_OwnsData)
		delete[] m_Verticies;
	m_Verticies = verts;
	m_VertAmount = numverts;
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat)*numverts, verts, usage);

	// gen and fill buffer with our indices.
	if (m_IBO == 0)
		glGenBuffers(1, &m_IBO);
	if (m_Indicies != nullptr && m_OwnsData)
		delete[] m_Indicies;
	m_Indicies = indices;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numindices, indices, usage);

	m_PrimitiveType = primitivetype;
	m_Usage = usage;
	CheckForGLErrors();
}

void Mesh::Init(const void* verts, int numverts, int vertexbytesize, GLenum usage, GLenum primitivetype)
{
	m_NumVerts = numverts;
	m_NumIndices = 0;

	// gen and fill buffer with our vertex attributes.
	if (m_VBO == 0)
		glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexbytesize, verts, usage);
	m_VertAmount = numverts;
	m_PrimitiveType = primitivetype;
	m_Usage = usage;
	CheckForGLErrors();
}

void Mesh::SetupAttributes(ShaderProgram* pShaderProgram)
{
	assert(m_VBO != 0);

	// bind our vertex and index buffers.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	if (m_IBO != 0)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	GLuint programhandle = pShaderProgram->GetProgram();

	// get the attribute locations.
	GLint aPos = glGetAttribLocation(programhandle, "a_Position");
	GLint aColor = glGetAttribLocation(programhandle, "a_Color");
	GLint aUV = glGetAttribLocation(programhandle, "a_UV");
	GLint aNormal = glGetAttribLocation(programhandle, "a_Normal");

	// setup our vbo and attributes.
	{
		// setup the position attribute.
		assert(aPos != -1);
		glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, pos));
		glEnableVertexAttribArray(aPos);

		// setup the color attribute.
		if (aColor != -1)
		{
			glVertexAttribPointer(aColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, color));
			glEnableVertexAttribArray(aColor);
		}

		// setup the uv attribute.
		if (aUV != -1)
		{
			glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, uv));
			glEnableVertexAttribArray(aUV);
		}

		// setup the normal attribute.
		if (aNormal != -1)
		{
			glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, normal));
			glEnableVertexAttribArray(aNormal);
		}
	}
}

void Mesh::SetupUniforms(GameObject* drawer, ShaderProgram* pShaderProgram, mat4* worldmat, mat4* camMat, mat4* projMat, mat4* normMat, Material* texturehandle, Material* secondarytexturehandle, Vector4 color)
{
	GLuint programhandle = pShaderProgram->GetProgram();

	// enable our shader program.
	glUseProgram(programhandle);

	// get the uniform locations.
	GLint uWorldMatrix = glGetUniformLocation(programhandle, "u_matWorld");
	GLint uViewMatrix = glGetUniformLocation(programhandle, "u_matView");
	GLint uProjMatrix = glGetUniformLocation(programhandle, "u_matProj");
	GLint uNormWorldMatrix = glGetUniformLocation(programhandle, "u_matNorm");
	GLint uCamPos = glGetUniformLocation(programhandle, "u_CameraPosition");
	GLint uTexture = glGetUniformLocation(programhandle, "u_Texture");
    GLint uSecondaryTexture = glGetUniformLocation(programhandle, "u_SecondaryTexture");
	GLint uColor = glGetUniformLocation(programhandle, "u_Color");
	GLint uColour = glGetUniformLocation(programhandle, "u_Colour");
	GLint uTime = glGetUniformLocation(programhandle, "u_Time");
	GLint uRandNum = glGetUniformLocation(programhandle, "u_RandNumber");
	GLint uReflection = glGetUniformLocation(programhandle, "u_ReflectionAmount");
    GLint uShineAmount = glGetUniformLocation(programhandle, "u_ShineAmount");
	GLint uCubeTexture = glGetUniformLocation(programhandle, "u_CubeTexture");
	GLint uScale = glGetUniformLocation(programhandle, "u_Scale");
	GLint uOn = glGetUniformLocation(programhandle, "u_On");
	// lighting uniforms
	GLint uLightPos = glGetUniformLocation(programhandle, "u_LightPos[0]");
	GLint uLightColor = glGetUniformLocation(programhandle, "u_LightColor[0]");
	//ripple uniforms
	GLint rippleSizeLoc = glGetUniformLocation(programhandle, "u_rippleSize");
	GLint ripplePositionsLoc = glGetUniformLocation(programhandle, "u_RipplePositions[0]");
	GLint rippleActiveLoc = glGetUniformLocation(programhandle, "u_RippleActive[0]");
	GLint rippleDecayLoc = glGetUniformLocation(programhandle, "u_RippleDecay[0]");
	GLint rippleRadiusMaxLoc = glGetUniformLocation(programhandle, "u_RippleMaxRadius[0]");
	GLint rippleRadiusMinLoc = glGetUniformLocation(programhandle, "u_RippleMinRadius[0]");
	GLint rippleSinTimeLoc = glGetUniformLocation(programhandle, "u_RippleSinTime[0]");

	// setup the texture.
	if (texturehandle != nullptr && uTexture != -1)
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, texturehandle->TextureHandle);
		glUniform1i(uTexture, 0);
	}

    if (secondarytexturehandle != nullptr && uSecondaryTexture != -1)
    {
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, secondarytexturehandle->TextureHandle);
        glUniform1i(uSecondaryTexture, 1);
    }

	if (uCubeTexture != -1)
	{
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_CUBE_MAP, secondarytexturehandle->TextureHandle);
		glUniform1i(uCubeTexture, 2);
	}
	if (uReflection != -1)
	{
		float reflectionAmount;
		reflectionAmount = texturehandle->ReflectAmount;
		if (secondarytexturehandle != nullptr)
			reflectionAmount += secondarytexturehandle->ReflectAmount;
		glUniform1f(uReflection, reflectionAmount);
	}
    if (uShineAmount != -1)
    {
		float shineAmount;
		shineAmount = texturehandle->ShineAmount;
		if (secondarytexturehandle != nullptr)
			shineAmount += secondarytexturehandle->ShineAmount;
		glUniform1f(uShineAmount, shineAmount);
    }
	//ripple setup
	GameScene* scene = (GameScene*)g_pGame->GetScene();
	if (ripplePositionsLoc != -1)
	{
		glUniform3fv(ripplePositionsLoc, GAME_ROCK_COUNT, &scene->GetRipplePos()[0].x);
	}
	if (rippleActiveLoc != -1)
	{
		glUniform1iv(rippleActiveLoc, GAME_ROCK_COUNT, &scene->GetRippleActive()[0]);
	}
	if (rippleDecayLoc != -1)
	{
		glUniform1fv(rippleDecayLoc, GAME_ROCK_COUNT, &scene->GetRippleDecay()[0]);
	}
	if (rippleRadiusMaxLoc != -1)
	{
		glUniform1fv(rippleRadiusMaxLoc, GAME_ROCK_COUNT, &scene->GetRippleMaxRadius()[0]);
	}
	if (rippleRadiusMinLoc != -1)
	{
		glUniform1fv(rippleRadiusMinLoc, GAME_ROCK_COUNT, &scene->GetRippleMinRadius()[0]);
	}
	if (rippleSinTimeLoc != -1)
	{
		glUniform1fv(rippleSinTimeLoc, GAME_ROCK_COUNT, &scene->GetRippleSinTime()[0]);
	}
	if (rippleSizeLoc != -1)
	{
		glUniform1f(rippleSizeLoc, 3.0f);
	}
	//Lights setup
	if (uLightPos != -1)
	{
		//get all lights in scene
		std::vector<LightObject*> Lights;
		for each(auto iterator in scene->GetLights())
		{
			Lights.push_back(iterator.second);
		}
		if (Lights.size() > 0)
		{
			//get all light distances from the game object and order them from closest to farthest
			LightObject** NearestLights = new LightObject*[LIGHT_EFFECTED_MAX];
			double* distanceToBeat = new double[LIGHT_EFFECTED_MAX];
			for (int i = 0; i < LIGHT_EFFECTED_MAX; i++)
			{
				NearestLights[i] = nullptr;
				distanceToBeat[i] = -1.0f;
			}

			for (unsigned int i = 0; i < Lights.size(); i++)
			{
				double dist = npw::DistanceBetweenPoints(drawer->GetPosition().x, drawer->GetPosition().y, drawer->GetPosition().z, Lights[i]->GetPosition().x, Lights[i]->GetPosition().y, Lights[i]->GetPosition().z);
				for (int j = 0; j < LIGHT_EFFECTED_MAX; j++)
				{
					//if dist actually beats a distance, replace the current distance with dist and push the list back (knocking off the last one)
					if (dist < distanceToBeat[j] || distanceToBeat[j] == -1.0f)
					{
						int counter = j + 1;
						double tempdist = distanceToBeat[j];
						LightObject* templight = NearestLights[j];
						while (counter < LIGHT_EFFECTED_MAX)
						{
							double tempdist2 = distanceToBeat[counter];
							LightObject* templight2 = NearestLights[counter];
							distanceToBeat[counter] = tempdist;
							NearestLights[counter] = templight;
							tempdist = tempdist2;
							templight = templight2;
							counter++;
						}
						distanceToBeat[j] = dist;
						NearestLights[j] = Lights[i];
						break;
					}
				}
			}

			//parse all information needed from the lights
			Vector3* lightPoses = new Vector3[LIGHT_EFFECTED_MAX];
			Vector4* lightColors = new Vector4[LIGHT_EFFECTED_MAX];
			for (int i = 0; i < LIGHT_EFFECTED_MAX; i++)
			{
				if (NearestLights[i] != nullptr)
				{
					lightPoses[i] = NearestLights[i]->GetPosition();
					lightColors[i] = NearestLights[i]->GetLightColor();
				}
				else
				{
					lightPoses[i] = Vector3(0, 0, 0);
					lightColors[i] = Vector4(0, 0, 0, 0);
				}
			}
			//send the info to the shader
			glUniform3fv(uLightPos, LIGHT_EFFECTED_MAX, &lightPoses[0].x);
			glUniform4fv(uLightColor, LIGHT_EFFECTED_MAX, &lightColors[0].x);

			//clean up
			delete[] lightPoses;
			delete[] lightColors;
			delete[] distanceToBeat;
			delete[] NearestLights;
		}
	}
	//matrix setup
	if (uWorldMatrix != -1)
	{
		glUniformMatrix4fv(uWorldMatrix, 1, false, &worldmat->m11);
	}

	if (uViewMatrix != -1)
	{
		glUniformMatrix4fv(uViewMatrix, 1, false, &camMat->m11);
	}

	if (uProjMatrix != -1)
	{
		glUniformMatrix4fv(uProjMatrix, 1, false, &projMat->m11);
	}

	if (uNormWorldMatrix != -1)
	{
		glUniformMatrix4fv(uNormWorldMatrix, 1, false, &normMat->m11);
	}
	//misc setup
	if (uColor != -1)
	{
		glUniform4f(uColor, color.x, color.y, color.z, color.w);
	}

	if (uColour != -1)
	{
		glUniform4f(uColour, color.x, color.y, color.z, color.w);
	}

	if (uCamPos != -1 && drawer != NULL)
	{
		glUniform3f(uCamPos, drawer->GetScene()->GetCamera()->GetPosition().x, drawer->GetScene()->GetCamera()->GetPosition().y, drawer->GetScene()->GetCamera()->GetPosition().z);
	}

	if (uRandNum != -1)
	{
		glUniform1f(uRandNum, float(rand() % 100));
	}

	if (uScale != -1)
	{
		Vector3 scale = Vector3(1.0f,1.0f,1.0f);
		if (drawer != nullptr)
		{
			scale = drawer->GetScale();
		}
		glUniform3f(uScale, scale.x, scale.y, scale.z);
	}

	if (uOn != -1)
	{
		glUniform1i(uOn, g_pGame->IsDamageEffectOn());
	}
	// setup time.
	if (uTime != -1)
	{
		glUniform1f(uTime, (float)MyGetSystemTime());
	}

	CheckForGLErrors();
}

void Mesh::Draw(ShaderProgram* pShaderProgram, GameObject* drawer)
{
	GLuint programhandle = pShaderProgram->GetProgram();

	//convert vert uvs based on drawer's scale


	// draw the shape.
	if (m_NumIndices > 0)
	{
		glDrawElements(m_PrimitiveType, m_NumIndices, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(m_PrimitiveType, 0, m_NumVerts);
	}

	GLint aPos = glGetAttribLocation(programhandle, "a_Position");
	GLint aColor = glGetAttribLocation(programhandle, "a_Color");
	GLint aUV = glGetAttribLocation(programhandle, "a_UV");
	GLint aNormal = glGetAttribLocation(programhandle, "a_Normal");

	// disable the attribute arrays used
	glDisableVertexAttribArray(aPos);

	if (aColor != -1)
		glDisableVertexAttribArray(aColor);

	if (aUV != -1)
		glDisableVertexAttribArray(aUV);

	if (aNormal != -1)
		glDisableVertexAttribArray(aNormal);

	CheckForGLErrors();
}
