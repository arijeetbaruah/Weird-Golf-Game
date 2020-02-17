#pragma once

#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"

enum MeshBuffer {
	VERTEX_BUFFER, COLOUR_BUFFER, TEXTURE_BUFFER,
	NORMAL_BUFFER, TANGENT_BUFFER, INDEX_BUFFER,
	MAX_BUFFER
};

#define RAW_WIDTH 1000
#define RAW_HEIGHT 1000

#define TEXTURE_SEPARATION 1.0f / 32.0f

class Mesh {
public:
	Mesh(void);
	~Mesh(void);
	

	Vector4* getColours() { return colours; }
	Vector3* getVertices() { return vertices; }
	int* getIndices() { return indices; }
	unsigned int getNumVertices() { return numVertices; }
	int getNumIndices() { return numIndices; }


protected:

	int numIndices;
	int* indices;
	
	Vector3* normals;

	unsigned int arrayObject;
	unsigned int bufferObject[MAX_BUFFER];
	unsigned int numVertices;
	unsigned int type;
	
	Vector3* vertices;
	Vector4* colours;

	Vector2* textureCoords;

	Vector3* tangents;
};


