#pragma once
#include <vector>
#include <memory>
#include "../Common/Vector2.h"
#include "../Common/Vector3.h"
#include "../Common/Vector4.h"

enum MeshBuffer
{
	VERTEX_BUFFER, COLOR_BUFFER, TEXTURE_BUFFER, NORMAL_BUFFER, TANGENT_BUFFER, INDEX_BUFFER, MAX_BUFFER
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	std::vector<NCL::Maths::Vector3>& GetNormals()
	{
		return normals;
	}

	std::vector<NCL::Maths::Vector2>& GetTextureCoords()
	{
		return textureCoords;
	}

	std::vector<NCL::Maths::Vector3>& GetVertices()
	{
		return vertices;
	}

	std::vector<NCL::Maths::Vector4>& GetColors()
	{
		return colors;
	}
protected:
	// void BufferData();

	std::vector<NCL::Maths::Vector3> normals;
																	    
	std::vector<NCL::Maths::Vector2> textureCoords;
																	    
	std::vector <NCL::Maths::Vector3> vertices;
	std::vector<NCL::Maths::Vector4> colors;

	unsigned int* indices;

	/*Vector3 GenerateTangent(const Vector3 &a, const Vector3 &b,
													const Vector3 &c, const Vector2 &ta,
													const Vector2 &tb, const Vector2 &tc);*/

	// void GenerateNormals();
	/*void GenerateTangents();
	Vector3* tangents;
	GLuint bumpTexture;*/
};

