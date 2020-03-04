#include "TriangleMeshPhysicsComponent.h"
#include "PhysxController.h"
#include <iostream>

TriangleMeshPhysicsComponent::TriangleMeshPhysicsComponent(PxTransform transform, GameObject* go, float mass, std::vector<PxVec3> verts, std::vector<PxU32> tris)
	: PhysicsComponent("TriangleMeshPhysicsComponent", transform, go) {
	PxTriangleMeshDesc meshDesc;

	meshDesc.points.count = verts.size();
	meshDesc.points.stride = sizeof(PxVec3);
	meshDesc.points.data = &verts[0];

	meshDesc.triangles.count = tris.size() / 3;
	meshDesc.triangles.stride = 3 * sizeof(PxU32);
	meshDesc.triangles.data = &tris[0];

	PxDefaultMemoryOutputStream writeBuffer;
	PxTriangleMeshCookingResult::Enum result;
	bool status = PhysxController::getInstance().Cooking()->cookTriangleMesh(meshDesc, writeBuffer, &result);

	PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	PxTriangleMesh* mesh = gPhysics->createTriangleMesh(readBuffer);
	PxTriangleMeshGeometry geom(mesh);

	PxShape* meshShape;
	if (actor) {
		actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
		meshShape = PxRigidActorExt::createExclusiveShape(*actor, geom, *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
	}
}

void TriangleMeshPhysicsComponent::Start() {
	PhysicsComponent::Start();
}

void TriangleMeshPhysicsComponent::Update() {
	PhysicsComponent::Update();
}
