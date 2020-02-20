#include "Mesh.h"

Mesh::Mesh()
{
	//for (int i = 0; i < MAX_BUFFER; i++)
	//{
	//	bufferObject[i] = 0;
	//}
	//indices = NULL;
	//numIndices = 0;
	//texture = 0;
	//textureCoords = NULL;
	//numVertices = 0;
	//vertices = NULL;
	//colors = NULL;
	//normals = NULL;
	//tangents = NULL;
	//bumpTexture = 0;
}

Mesh::~Mesh()
{

}

//void Mesh::GenerateNormals()
//{
//	if (!normals)
//	{
//		normals = new Vector3[numVertices];
//	}
//	for (GLuint i = 0; i < numVertices; i++)
//	{
//		normals[i] = Vector3();
//	}
//	if (indices)
//	{
//		for (GLuint i = 0; i < numIndices; i += 3)
//		{
//			unsigned int a = indices[i];
//			unsigned int b = indices[i + 1];
//			unsigned int c = indices[i + 2];
//
//			Vector3 normal = Vector3::Cross((vertices[b] - vertices[a]), (vertices[c] - vertices[a]));
//
//			normals[a] += normal;
//			normals[b] += normal;
//			normals[c] += normal;
//		}
//	}
//	else
//	{
//		for (GLuint i = 0; i < numVertices; i += 3)
//		{
//			Vector3& a = vertices[i];
//			Vector3& b = vertices[i + 1];
//			Vector3& c = vertices[i + 2];
//
//			Vector3 normal = Vector3::Cross(b-a, c-a);
//			normals[i] = normal;
//			normals[i + 1] = normal;
//			normals[i + 2] = normal;
//		}
//	}
//	for (GLuint i = 0; i < numVertices; i++)
//	{
//		normals[i].Normalize();
//	}
//}

//void Mesh::BufferData()
//{
//	glBindVertexArray(arrayObject);
//	glGenBuffers(1, &bufferObject[MeshBuffer::VERTEX_BUFFER]);
//	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[MeshBuffer::VERTEX_BUFFER]);
//	glBufferData(GL_ARRAY_BUFFER, numVertices* sizeof(Vector3), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(MeshBuffer::VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(MeshBuffer::VERTEX_BUFFER);
//	if (indices)
//	{
//		glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject[INDEX_BUFFER]);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);
//	}
//	if (textureCoords)
//	{
//		glGenBuffers(1, &bufferObject[MeshBuffer::TEXTURE_BUFFER]);
//		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[MeshBuffer::TEXTURE_BUFFER]);
//		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector2), textureCoords, GL_STATIC_DRAW);
//		glVertexAttribPointer(MeshBuffer::TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(MeshBuffer::TEXTURE_BUFFER);
//	}
//	if (colors)
//	{
//		glGenBuffers(1, &bufferObject[COLOR_BUFFER]);
//		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[MeshBuffer::COLOR_BUFFER]);
//		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector4), colors, GL_STATIC_DRAW);
//		glVertexAttribPointer(MeshBuffer::COLOR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(MeshBuffer::COLOR_BUFFER);
//	}
//	if (normals)
//	{
//		glGenBuffers(1, &bufferObject[NORMAL_BUFFER]);
//		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[NORMAL_BUFFER]);
//		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), normals, GL_STATIC_DRAW);
//		glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(NORMAL_BUFFER);
//	}
//	if (tangents)
//	{
//		glGenBuffers(1, &bufferObject[TANGENT_BUFFER]);
//		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TANGENT_BUFFER]);
//		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), tangents, GL_STATIC_DRAW);
//		glVertexAttribPointer(TANGENT_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(TANGENT_BUFFER);
//	}
//	glBindVertexArray(0);
//}

//void Mesh::GenerateTangents()
//{
//	if (!tangents)
//	{
//		tangents = new Vector3[numVertices];
//	}
//	if (!textureCoords)
//	{
//		return;
//	}
//	for (GLuint i = 0; i < numVertices; i++)
//	{
//		tangents[i] = Vector3();
//	}
//
//	if (indices)
//	{
//		for (GLuint i = 0; i < numIndices; i += 3)
//		{
//			int a = indices[i];
//			int b = indices[i + 1];
//			int c = indices[i + 2];
//			Vector3 tangent = GenerateTangent(vertices[a], vertices[b], vertices[c], textureCoords[a], textureCoords[b], textureCoords[c]);
//
//			tangents[a] += tangent;
//			tangents[b] += tangent;
//			tangents[c] += tangent;
//		}
//	}
//	else
//	{
//		for (GLuint i = 0; i < numVertices; i += 3)
//		{
//			Vector3 tangent = GenerateTangent(vertices[i], vertices[i + 1], vertices[i + 2], textureCoords[i], textureCoords[i + 1], textureCoords[i + 2]);
//
//			tangents[i] += tangent;
//			tangents[i + 1] += tangent;
//			tangents[i + 2] += tangent;
//		}
//	}
//	for (GLuint i = 0; i < numVertices; i++)
//	{
//		tangents[i].Normalize();
//	}
//}

//Vector3 Mesh::GenerateTangent(const Vector3& a, const Vector3& b,
//	const Vector3& c, const Vector2& ta,
//	const Vector2& tb, const Vector2& tc)
//{
//	Vector2 coord1 = tb - ta;
//	Vector2 coord2 = tc - ta;
//
//	Vector3 vertex1 = b - a;
//	Vector3  vertex2 = c - a;
//
//	Vector3 axis = Vector3(vertex1 * coord2.y - vertex2 * coord1.y);
//
//	float factor = 1.0f / (coord1.x * coord2.y - coord2.x * coord1.y);
//	return axis * factor;
//}