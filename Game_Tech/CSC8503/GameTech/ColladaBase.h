#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include "tinyxml2.h"

using std::vector;
typedef struct Int3
{
	int x, y, z;
}pointInfor;
typedef struct Float3
{
	float x, y, z;
}vertexInfor;
typedef struct Float2
{
	float x, y;
}textureInfor;
typedef struct  Temp_Mesh
{
	vector<vertexInfor> vertices;
	vector<vertexInfor> normals;
	vector<textureInfor> texcoords;
	vector<pointInfor> indices;
}meshTemp;
typedef struct  EnjoyMesh
{
	vector<vertexInfor> vertices;
	vector<vertexInfor> normals;
	vector<textureInfor> texcoords;
	vector<int> indices;
}meshInfor;

/*
	Simple Collada loader, which only supports simple Collada format.
*/

class ColladaBase
{
public:
	ColladaBase(const char* path);

	vector<EnjoyMesh> GetMeshes(){	return meshes;		}
	auto GetNumMeshes()			{	return numMeshes;	}
protected:
	vector<meshTemp> temp_meshes;
	vector<meshInfor> meshes;
	int numMeshes;
};
