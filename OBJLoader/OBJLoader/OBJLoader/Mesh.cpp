#include "Mesh.h"

Mesh::Mesh(void) {

	indices = NULL;
	numIndices = 0;

	tangents = NULL;


	for (int i = 0; i < MAX_BUFFER; ++i) {
		bufferObject[i] = 0;
		
	}
	//glGenVertexArrays(1, &arrayObject);
	
	numVertices = 0;
	vertices = NULL;
	colours = NULL;

	textureCoords = NULL;

	normals = NULL;

}

Mesh ::~Mesh(void) {
	//glDeleteVertexArrays(1, &arrayObject);
	//glDeleteBuffers(MAX_BUFFER, bufferObject);
	delete[] vertices;
	delete[] colours;

	delete[] textureCoords;
	delete[] indices;
	delete[] normals;

	delete[] tangents;
}