#pragma once
#include "PhysicsComponent.h"
class TriangleMeshPhysicsComponent : public PhysicsComponent {
public:
	TriangleMeshPhysicsComponent(PxTransform transform, float mass, std::vector<PxVec3> verts, std::vector<PxU32> tris, PxMaterial* mMaterial);

	virtual void Start() override;
	virtual void Update(float dt) override;
};

