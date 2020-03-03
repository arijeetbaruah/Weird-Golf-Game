#include "EnjoyCollada.h"

EnjoyCollada::EnjoyCollada(const char* path)
{
	tinyxml2::XMLDocument xml;
	xml.LoadFile(path);
	auto* COLLADA = xml.FirstChildElement("COLLADA");
	auto* library_geometries = COLLADA->FirstChildElement("library_geometries");
	std::vector<tinyxml2::XMLElement*> geometries;
	for (auto* current_geometry = library_geometries->FirstChildElement("geometry");
		current_geometry != nullptr;
		current_geometry = current_geometry->NextSiblingElement())
	{
		geometries.push_back(current_geometry);
	}
	numMeshes = geometries.size();
	for (auto* item : geometries)
	{
		auto* mesh = item->FirstChildElement("mesh");
		auto* sources = mesh->FirstChildElement("source");

		auto* vertices = sources;
		sources = sources->NextSiblingElement();

		auto* normals = sources;
		sources = sources->NextSiblingElement();

		std::vector<tinyxml2::XMLElement*> texCoords;

		for (;
			sources != nullptr;
			sources = sources->NextSiblingElement("source"))
		{
			texCoords.push_back(sources);
		}

		#pragma region Read Temp Mesh
		TempMesh newMesh;
		#pragma region MeshData
		// Vertices
		auto* vertex_array = vertices->FirstChildElement("float_array")->GetText();
		std::stringstream ss(vertex_array);
		while (!ss.eof())
		{
			Float3 newVert;
			ss >> newVert.x >> newVert.y >> newVert.z;
			newMesh.vertices.push_back(newVert);
		}
		// End of vertices

		// Normals
		auto* normal_array = normals->FirstChildElement("float_array")->GetText();
		ss = std::stringstream(normal_array);
		while (!ss.eof())
		{
			Float3 newNorm;
			ss >> newNorm.x >> newNorm.y >> newNorm.z;
			newMesh.normals.push_back(newNorm);
		}
		// End of Normals

		// Texcoords
		std::vector<const char*> texcoord_arries;
		for (auto* item : texCoords)
		{
			texcoord_arries.push_back(item->FirstChildElement("float_array")->GetText());
		}

		for (auto* item : texcoord_arries)
		{
			ss = std::stringstream(item);
			newMesh.texcoords.push_back(vector<Float2>());
			while (!ss.eof())
			{
				Float2 newTexcoord;
				ss >> newTexcoord.x >> newTexcoord.y;
				newMesh.texcoords.back().push_back(newTexcoord);
			}
		}
		// End of Texcoords

		// Indices
		for (auto* faces = mesh->FirstChildElement("triangles");
			faces != nullptr;
			faces = faces->NextSiblingElement("triangles"))
		{
			tinyxml2::XMLElement* indices = nullptr;

			if (faces != nullptr)
			{
				indices = faces->FirstChildElement("p");
			}
			newMesh.indices.push_back(vector<Int3>());
			ss = std::stringstream(indices->GetText());
			while (!ss.eof())
			{
				Int3 newIndex;
				ss >> newIndex.x >> newIndex.y >> newIndex.z;
				newMesh.indices.back().push_back(newIndex);
			}
		}
		// End of indices
		#pragma endregion MeshData
		temp_meshes.push_back(newMesh);
#pragma endregion Read Temp Mesh

	}
	for (auto mesh_item : temp_meshes)
		{
			int index = 0;
			EnjoyMesh result_mesh;
			int texIndex = 0;
			for (auto index_item_group : mesh_item.indices)
			{
				for (auto index_item : index_item_group)
				{

					Float3 vert = mesh_item.vertices[index_item.x];
					Float3 norm = mesh_item.normals[index_item.y];
					Float2 texc = mesh_item.texcoords[texIndex][index_item.z];

					result_mesh.vertices.push_back(vert);
					result_mesh.normals.push_back(norm);
					result_mesh.texcoords.push_back(texc);
					result_mesh.indices.push_back(index++);
				}
				texIndex++;
			}
			meshes.push_back(result_mesh);
		}
}
