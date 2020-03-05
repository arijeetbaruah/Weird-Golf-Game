#include "EnjoyColladaMesh.h"

EnjoyColladaMesh::EnjoyColladaMesh(const char* path): EnjoyCollada(path)
{
	for (auto item : meshes)
	{
	 	std::vector<NCL::Maths::Vector3> vertices;
		std::vector<NCL::Maths::Vector3> normals;
		std::vector<NCL::Maths::Vector2> texcoords;
		std::vector<NCL::Maths::Vector4> colors;
		std::vector<unsigned int> indicies;
		for (int i = 0; i < item.vertices.size(); i++)
		{
			vertices.push_back(NCL::Maths::Vector3(item.vertices[i].x, item.vertices[i].y, item.vertices[i].z));
			normals.push_back(NCL::Maths::Vector3(item.normals[i].x, item.normals[i].y, item.normals[i].z));
			texcoords.push_back(NCL::Maths::Vector2(item.texcoords[i].x, 1 - item.texcoords[i].y));
			indicies.push_back(item.indices[i]);
			colors.push_back(NCL::Maths::Vector4(1, 1, 1, 1));
		}

		NCL::PS4::PS4Mesh* newMesh = new NCL::PS4::PS4Mesh();

		newMesh->SetVertexPositions(vertices);
		newMesh->SetVertexNormals(normals);
		newMesh->SetVertexTextureCoords(texcoords);
		newMesh->SetVertexColors(colors);
		newMesh->SetVertexIndices(indicies);
		newMesh->UpdateMesh();
		ChildMeshes.push_back(newMesh);
	}
}

EnjoyColladaMesh::~EnjoyColladaMesh()
{
	for (auto* item : ChildMeshes)
	{
		delete item;
	}
}
