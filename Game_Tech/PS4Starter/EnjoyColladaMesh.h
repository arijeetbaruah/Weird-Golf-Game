#pragma once

#include "EnjoyCollada.h"
#include "../Plugins/PlayStation4/PS4RendererBase.h"
#include "../Plugins/PlayStation4/PS4Mesh.h"
#include "../Common/Maths.h"

class EnjoyColladaMesh: public EnjoyCollada
{
public:
	EnjoyColladaMesh(const char* path);
	~EnjoyColladaMesh();

	std::vector<NCL::PS4::PS4Mesh*> ChildMeshes;
};

