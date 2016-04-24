#include "CommonHeader.h"

Mesh* Mesh::CreateBox(Vector2 size, bool isAnimated)
{
    VertexFormat* verts = new VertexFormat[4];

    verts[0] = VertexFormat( -size.x/2, -size.y/2, 0, 255,255,255,255, 0,0, 0,0,-1 );
    verts[1] = VertexFormat( -size.x/2,  size.y/2, 0, 255,255,255,255, 0,1, 0,0,-1 );
    verts[2] = VertexFormat(  size.x/2,  size.y/2, 0, 255,255,255,255, 1,1, 0,0,-1 );
    verts[3] = VertexFormat(  size.x/2, -size.y/2, 0,  255,255,255,255, 1,0, 0,0,-1 );

    unsigned int* indices = new unsigned int[6];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;

	float minX = verts[0].pos.x;
	float maxX = verts[0].pos.x;
	float minY = verts[0].pos.y;
	float maxY = verts[0].pos.y;

	for (uint i = 1; i < 4; i++)
	{
		minX = npw::Minimum(minX, verts[i].pos.x);
		maxX = npw::Maximum(maxX, verts[i].pos.x);
		minY = npw::Minimum(minY, verts[i].pos.y);
		maxY = npw::Maximum(maxY, verts[i].pos.y);
	}

	Mesh* pMesh;
		if (isAnimated)
			pMesh = new AnimatedMesh();
		else
			pMesh = new Mesh();
	pMesh->Init(verts, 4, indices, 6, GL_STATIC_DRAW);
	pMesh->SetWidth(size.x);
	pMesh->SetHeight(size.y);

    return pMesh;
};

Mesh* Mesh::GenerateTexturePlane(float width, float height, int vertCountX, int vertCountZ, int tileCountPerTextureX, int tileCountPerTextureZ)
{
    // find the width / height each *tile* will be
    float widthPerTile = width / (float)vertCountX;
    float depthPerTile = height / (float)vertCountZ;
    //allocate verticies and indicies
    int indexCount = ((vertCountX - 1) * (vertCountZ - 1)) * 6;
    VertexFormat* verticies = new   VertexFormat[(vertCountX * vertCountZ)];
    unsigned int* indicies = new unsigned int[indexCount];
    //helper variables used for spacing the verticies
    float currentTileX = 0.0f;
    float currentTileZ = 0.0f;
    //setup all the verticies (positions,uvs)
    for (int i = 0; i < vertCountX * vertCountZ; i++)
    {
        verticies[i].pos.x = (widthPerTile * currentTileX);
        verticies[i].pos.y = 0.0f;
        verticies[i].pos.z = (depthPerTile * currentTileZ);
        verticies[i].color.a = 255;
        verticies[i].color.r = 255;
        verticies[i].color.g = 255;
        verticies[i].color.b = 255;
        verticies[i].uv.x = (float)currentTileX / (float)tileCountPerTextureX;
        verticies[i].uv.y = (float)currentTileZ / (float)tileCountPerTextureZ;
        verticies[i].normal.x = 0;
        verticies[i].normal.y = -1;
        verticies[i].normal.z = 0;

        currentTileX++;
        if (currentTileX == vertCountX)
        {
            currentTileX = 0.0f;
            currentTileZ++;
        }
        
    }
    //setup all the indicies to create a series of squares/rectangles for the verticies
    int count = 0;
    for (int i = 0; i < vertCountZ - 1; i++)
    {
        for (int j = 0; j < vertCountX - 1; j++)
        {
            int topLeftIndex = i * vertCountX + j;
            indicies[count + 5] = topLeftIndex;
            indicies[count + 4] = topLeftIndex + 1;
            indicies[count + 3] = topLeftIndex + (vertCountX);

            indicies[count + 2] = topLeftIndex + 1;
            indicies[count + 1] = topLeftIndex + (vertCountX + 1);
            indicies[count + 0] = topLeftIndex + (vertCountX);
            count += 6;
        }
    }
    Mesh* pMesh = new Mesh();
	pMesh->Init(verticies, (vertCountX * vertCountZ), indicies, indexCount, GL_STATIC_DRAW, GL_TRIANGLES);
	pMesh->SetWidth(width);
	pMesh->SetHeight(height);

    return pMesh;
}
Mesh* Mesh::GenerateSkyBox(float size)
{
    VertexFormat* verticies = new VertexFormat[8]
    {
        {-size / 2, -size / 2, -size / 2, 255, 255, 255, 255, 0, 0, 0, 0, 0 },//0
        { size / 2, -size / 2, -size / 2, 255, 255, 255, 255, 0, 0, 0, 0, 0 },//1
        { size / 2, size / 2, -size / 2, 255, 255, 255, 255, 0, 0, 0, 0, 0 },//2
        { -size / 2, size / 2, -size / 2, 255, 255, 255, 255, 0, 0, 0, 0, 0 },//3

        { -size / 2, -size / 2, size / 2, 255, 255, 255, 255, 0, 0, 0, 0, 0 },//4
        { size / 2, -size / 2, size / 2, 255, 255, 255, 255, 0, 0, 0, 0, 0 },//5
        { size / 2, size / 2, size / 2, 255, 255, 255, 255, 0, 0, 0, 0, 0 },//6
        { -size / 2, size / 2, size / 2, 255, 255, 255, 255, 0, 0, 0, 0, 0 }//7
      
        //7-----6
        //      |
        //4-----5   
   //3-----2
   //      |
   //0-----1
    };
    unsigned int* indicies = new unsigned int[36] {
        0,1,2,2,3,0,//front
        4,7,6,6,5,4,//back
        3,2,6,6,7,3,//top
        0,4,5,5,1,0,//bottom
        0,3,7,7,4,0,//left
        5,6,2,2,1,5//right
    };
    Mesh* pMesh = new Mesh();
    pMesh->Init(verticies, 8, indicies, 36, GL_STATIC_DRAW);
    pMesh->SetWidth(size);
    pMesh->SetHeight(size);
    return pMesh;
}
Mesh* Mesh::GenerateTextureBox(float size)
{
    VertexFormat* verticies = new VertexFormat[24]
    {
        {-size / 2, -size / 2, -size / 2, 255, 255, 255, 255, 0, 0, 0, 0, -1 },
        { size / 2, -size / 2, -size / 2, 255, 255, 255, 255, 0, 1, 0, 0, -1 },
        { size / 2, size / 2, -size / 2, 255, 255, 255, 255, 1, 1, 0, 0, -1 },
        { -size / 2, size / 2, -size / 2, 255, 255, 255, 255, 1, 0, 0, 0, -1 },

        { -size / 2, -size / 2, size / 2, 255, 255, 255, 255, 0, 0, 0, 0, 1 },
        { size / 2, -size / 2, size / 2, 255, 255, 255, 255, 0, 1, 0, 0, 1 },
        { size / 2, size / 2, size / 2, 255, 255, 255, 255, 1, 1, 0, 0, 1 },
        { -size / 2, size / 2, size / 2, 255, 255, 255, 255, 1, 0, 0, 0, 1 },

        { -size / 2, -size / 2, -size / 2, 255, 255, 255, 255, 0, 0, -1, 0, 0 },
        { -size / 2, -size / 2, size / 2, 255, 255, 255, 255, 0, 1, -1, 0, 0 },
        { -size / 2, size / 2, size / 2, 255, 255, 255, 255, 1, 1, -1, 0, 0 },
        { -size / 2, size / 2, -size / 2, 255, 255, 255, 255, 1, 0, -1, 0, 0 },

        { size / 2, -size / 2, -size / 2, 255, 255, 255, 255, 0, 0, 1, 0, 0 },
        { size / 2, -size / 2, size / 2, 255, 255, 255, 255, 0, 1, 1, 0, 0 },
        { size / 2, size / 2, size / 2, 255, 255, 255, 255, 1, 1, 1, 0, 0 },
        { size / 2, size / 2, -size / 2, 255, 255, 255, 255, 1, 0, 1, 0, 0 },

        { -size / 2, -size / 2, size / 2, 255, 255, 255, 255, 0, 0, 0, -1, 0 },
        { size / 2, -size / 2, size / 2, 255, 255, 255, 255, 0, 1, 0, -1, 0 },
        { size / 2, -size / 2, -size / 2, 255, 255, 255, 255, 1, 1, 0, -1, 0 },
        { -size / 2, -size / 2, -size / 2, 255, 255, 255, 255, 1, 0, 0, -1, 0 },

        { -size / 2, size / 2, size / 2, 255, 255, 255, 255, 0, 0, 0, 1, 0 },
        { size / 2, size / 2, size / 2, 255, 255, 255, 255, 0, 1, 0, 1, 0 },
        { size / 2, size / 2, -size / 2, 255, 255, 255, 255, 1, 1, 0, 1, 0 },
        { -size / 2, size / 2, -size / 2, 255, 255, 255, 255, 1, 0, 0, 1, 0 }
    };

    unsigned int* indicies = new unsigned int[36] {
        0, 2, 1, 0, 3, 2, //cw
            4, 5, 6, 4, 6, 7, //ccw
            8, 9, 10, 8, 10, 11, //ccw
            12, 14, 13, 12, 15, 14, //cw
            16, 18, 17, 16, 19, 18, //cw
            20, 21, 22, 20, 22, 23 //ccw
	};

	float minX = verticies[0].pos.x;
	float maxX = verticies[0].pos.x;
	float minY = verticies[0].pos.y;
	float maxY = verticies[0].pos.y;

	for (uint i = 1; i < 24; i++)
	{
		minX = npw::Minimum(minX, verticies[i].pos.x);
		maxX = npw::Maximum(maxX, verticies[i].pos.x);
		minY = npw::Minimum(minY, verticies[i].pos.y);
		maxY = npw::Maximum(maxY, verticies[i].pos.y);
	}

    Mesh* pMesh = new Mesh();
	pMesh->Init(verticies, 24, indicies, 36, GL_STATIC_DRAW);
	pMesh->SetWidth(size);
	pMesh->SetHeight(size);

    return pMesh;
}

Mesh* Mesh::GenerateTexturePlatform(float sizeX, float sizeY, float sizeZ)
{
    VertexFormat* verticies = new VertexFormat[24]
    {
        {-sizeX / 2, -sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 0, 0, 0, 0, -1 },
        { sizeX / 2, -sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 0, 1, 0, 0, -1 },
        { sizeX / 2, sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 1, 1, 0, 0, -1 },
        { -sizeX / 2, sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 1, 0, 0, 0, -1 },

        { -sizeX / 2, -sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 0, 0, 0, 0, 1 },
        { sizeX / 2, -sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 0, 1, 0, 0, 1 },
        { sizeX / 2, sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 1, 1, 0, 0, 1 },
        { -sizeX / 2, sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 1, 0, 0, 0, 1 },

        { -sizeX / 2, -sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 0, 0, -1, 0, 0 },
        { -sizeX / 2, -sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 0, 1, -1, 0, 0 },
        { -sizeX / 2, sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 1, 1, -1, 0, 0 },
        { -sizeX / 2, sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 1, 0, -1, 0, 0 },

        { sizeX / 2, -sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 0, 0, 1, 0, 0 },
        { sizeX / 2, -sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 0, 1, 1, 0, 0 },
        { sizeX / 2, sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 1, 1, 1, 0, 0 },
        { sizeX / 2, sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 1, 0, 1, 0, 0 },

        { -sizeX / 2, -sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 0, 0, 0, -1, 0 },
        { sizeX / 2, -sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 0, 1, 0, -1, 0 },
        { sizeX / 2, -sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 1, 1, 0, -1, 0 },
        { -sizeX / 2, -sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 1, 0, 0, -1, 0 },

        { -sizeX / 2, sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 0, 0, 0, 1, 0 },
        { sizeX / 2, sizeY / 2, sizeZ / 2, 255, 255, 255, 255, 0, 1, 0, 1, 0 },
        { sizeX / 2, sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 1, 1, 0, 1, 0 },
        { -sizeX / 2, sizeY / 2, -sizeZ / 2, 255, 255, 255, 255, 1, 0, 0, 1, 0 }
    };

    unsigned int* indicies = new unsigned int[36] {
        0, 2, 1, 0, 3, 2, //cw
            4, 5, 6, 4, 6, 7, //ccw
            8, 9, 10, 8, 10, 11, //ccw
            12, 14, 13, 12, 15, 14, //cw
            16, 18, 17, 16, 19, 18, //cw
            20, 21, 22, 20, 22, 23 //ccw
	};

    Mesh* pMesh = new Mesh();
	pMesh->Init(verticies, 24, indicies, 36, GL_STATIC_DRAW);
	pMesh->SetWidth(sizeX);
	pMesh->SetHeight(sizeY);

    return pMesh;
}

Mesh* Mesh::LoadOBJFile(const char* objfilename, Vector3 scale)
{
	long length = 0;
	char* buffer = LoadCompleteFile(objfilename, &length);
	if (buffer == 0 || length == 0)
	{
		delete buffer;
		return nullptr;
	}
	char* next_token = 0;
	char* line = strtok_s(buffer, "\n", &next_token);

	std::vector<Vector3> positions;
	std::vector<Vector2> uvCoords;
	std::vector<Vector3> normals;
	std::vector<VertexFormat> verts;
	std::vector<unsigned int> inds;

	unsigned int indcounter = 0;

	while (line)
	{
		Vector3 Pos;
		Vector2 Uv;
		Vector3 Normal;

		int p1;
		int uv1;
		int norm1;

		int p2;
		int uv2;
		int norm2;

		int p3;
		int uv3;
		int norm3;

		if (sscanf_s(line, "v %f %f %f", &Pos.x, &Pos.y, &Pos.z))
		{
			positions.push_back(Pos);
		}
		else if (sscanf_s(line, "vt %f %f", &Uv.x, &Uv.y))
		{
			uvCoords.push_back(Uv);
		}
		else if (sscanf_s(line, "vn %f %f %f", &Normal.x, &Normal.y, &Normal.z))
		{
			normals.push_back(Normal);
		}
		else if (sscanf_s(line, "f %u/%u/%u  %u/%u/%u  %u/%u/%u", &p1, &uv1, &norm1, &p2, &uv2, &norm2, &p3, &uv3, &norm3))
		{
			verts.push_back(VertexFormat(
				positions[p1 - 1].x * scale.x, positions[p1 - 1].y * scale.y, positions[p1 - 1].z * scale.z,
				255,255,255,255,
				uvCoords[uv1 - 1].x, uvCoords[uv1 - 1].y,
				normals[norm1 - 1].x, normals[norm1 - 1].y, normals[norm1 - 1].z));
			verts.push_back(VertexFormat(
				positions[p2 - 1].x * scale.x, positions[p2 - 1].y * scale.y, positions[p2 - 1].z * scale.z,
				255,255,255,255,
				uvCoords[uv2 - 1].x, uvCoords[uv2 - 1].y,
				normals[norm2 - 1].x, normals[norm2 - 1].y, normals[norm2 - 1].z));
			verts.push_back(VertexFormat(
				positions[p3 - 1].x * scale.x, positions[p3 - 1].y * scale.y, positions[p3 - 1].z * scale.z,
				255,255,255,255,
				uvCoords[uv3 - 1].x, uvCoords[uv3 - 1].y,
				normals[norm3 - 1].x, normals[norm3 - 1].y, normals[norm3 - 1].z));
			inds.push_back(indcounter);
			inds.push_back(indcounter + 1);
			inds.push_back(indcounter + 2);
			indcounter += 3;
		}
		line = strtok_s(0, "\n", &next_token);
	}

	float minX = positions[0].x;
	float maxX = positions[0].x;
	float minY = positions[0].y;
	float maxY = positions[0].y;

	for (uint i = 1; i < positions.size(); i++)
	{
		minX = npw::Minimum(minX, positions[i].x);
		maxX = npw::Maximum(maxX, positions[i].x);
		minY = npw::Minimum(minY, positions[i].y);
		maxY = npw::Maximum(maxY, positions[i].y);
	}

    VertexFormat* pointerverts = new VertexFormat[verts.size()];
    for (unsigned int i = 0; i < verts.size(); i++)
        pointerverts[i] = verts[i];
    unsigned int* pointerinds = new unsigned int[inds.size()];
    for (unsigned int i = 0; i < inds.size(); i++)
        pointerinds[i] = inds[i];

	Mesh* pMesh = new Mesh();
	pMesh->Init(pointerverts, verts.size(), pointerinds, inds.size(), GL_STATIC_DRAW);
	pMesh->SetWidth((maxX - minX) * scale.x);
	pMesh->SetHeight((maxY - minY) * scale.y);

	return pMesh;
}

Mesh* Mesh::GenerateFont(TTF::Font* aFont, float aScale, TTF::CodePoint aCodePoint)
{
	// Fonts tend to be huge - lower the scale
	aScale *= 0.001f;

    // Load the font triangulator
    TTF::Triangulator2DI triangulator;
    aFont->TriangulateGlyph(aCodePoint, triangulator);

    // Read the font and put them in a vector
    std::vector<VertexFormat> points;
    int i = -1;
    for (auto tri : triangulator) 
    {
        i++;
        VertexFormat form0;
        VertexFormat form1;
        VertexFormat form2;

        form0.pos.x = triangulator[tri.i0].x * aScale;
		form0.pos.y = triangulator[tri.i0].y * aScale;
		form1.pos.x = triangulator[tri.i1].x * aScale;
		form1.pos.y = triangulator[tri.i1].y * aScale;
		form2.pos.x = triangulator[tri.i2].x * aScale;
		form2.pos.y = triangulator[tri.i2].y * aScale;

        points.push_back(form0);
        points.push_back(form1);
        points.push_back(form2);
    }

    // Create a new size int and a new array of indices
    uint size = points.size();
	uint* indices = new uint[size]();

	VertexFormat* verts = new VertexFormat[size]();

    // Get the minimum and maximum of each point
	if (points.size() == 0)
		return nullptr;

    float minX = points[0].pos.x;
    float maxX = points[0].pos.x;
    float minY = points[0].pos.y;
    float maxY = points[0].pos.y;

    for (uint i = 1; i < size; i++)
    {
        minX = npw::Minimum(minX, points[i].pos.x);
        maxX = npw::Maximum(maxX, points[i].pos.x);
        minY = npw::Minimum(minY, points[i].pos.y);
        maxY = npw::Maximum(maxY, points[i].pos.y);
    }

    // Transfer data from points vector to verts array
    // Setting indices equal to i
    for (uint i = 0; i < size; i++)
    {
        // Position
        points[i].pos.z = 0;
        points[i].uv.x = points[i].pos.x;
        points[i].uv.y = points[i].pos.y;

        // UV
        npw::LockBetweenRange(points[i].uv.x, minX, maxX, 0.0f, 1.0f);
        npw::LockBetweenRange(points[i].uv.y, minY, maxY, 0.0f, 1.0f);

        // Color
        points[i].color.r = 255;
        points[i].color.g = 255;
        points[i].color.b = 255;
        points[i].color.a = 255;

        // Normals
        points[i].normal.x = 0;
        points[i].normal.y = 0;
        points[i].normal.z = -1;

        // Indices
		verts[i] = points[i];
        indices[i] = i;
    }

    Mesh* mesh = new Mesh();
    mesh->Init(verts, size, indices, size, GL_STATIC_DRAW);
	mesh->SetWidth(maxX - minX);
	mesh->SetHeight(maxY - minY);

    return mesh;
}

VertexFormat* Mesh::GenerateParticle(float size)
{
    VertexFormat* verts = new VertexFormat[4];

    verts[0] = VertexFormat(-size / 2, -size / 2, 0, 255, 255, 255, 255, 0, 0, 0, 0, -1);
    verts[1] = VertexFormat(-size / 2, size / 2, 0, 255, 255, 255, 255, 0, 1, 0, 0, -1);
    verts[2] = VertexFormat(size / 2, size / 2, 0, 255, 255, 255, 255, 1, 1, 0, 0, -1);
    verts[3] = VertexFormat(size / 2, -size / 2, 0, 255, 255, 255, 255, 1, 0, 0, 0, -1);

    return verts;
}