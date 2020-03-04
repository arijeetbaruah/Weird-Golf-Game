#pragma once
#include "PhysicsComponent.h"
#include <iostream>
#include <vector>

class TriangleMeshPhysicsComponent : public PhysicsComponent {
public:
	TriangleMeshPhysicsComponent(PxTransform transform, GameObject* go, float mass, std::vector<PxVec3> verts, std::vector<PxU32> tris);

	virtual void Start() override;
	virtual void Update() override;

	void setAsTrigger() = delete;
};

