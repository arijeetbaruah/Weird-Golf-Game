#include "Test.h"

int main()
{
	OBJMesh* mesh = new OBJMesh("TestLevel.obj");
	Vector3* vertices = mesh->getVertices();
	int* indices = mesh->getIndices();

	std::cout << "VERTICES: " << std::endl;
	int vertexCount = 0;

	for (int i = 0; i < mesh->getNumVertices(); i++)
	{
		vertexCount++;
		std::cout << vertices[i].x << ", " << vertices[i].y << ", " << vertices[i].z << std::endl;
	}
	std::cout << "VERTEX COUNT: " << vertexCount << std::endl;
	std::cout << "\n\n\n\n\n" << std::endl;

	std::cout << "INDICES: " << std::endl;
	std::cout << "num indices: " << mesh->getNumIndices() << std::endl;

	for (int i = 0; i < mesh->getNumIndices(); i++)
	{
		std::cout << indices[i] << std::endl;
	}
}