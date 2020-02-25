#include "TriangleMeshPhysicsComponent.h"

TriangleMeshPhysicsComponent::TriangleMeshPhysicsComponent(PxTransform transform, float mass, std::vector<PxVec3> verts, std::vector<PxU32> tris)
	: PhysicsComponent("SpherePhysicsComponent") {
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

	PxRigidDynamic* meshActor = gPhysics->createRigidDynamic(transform);
	PxShape* meshShape;
	if (meshActor) {
		meshActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
		meshShape = PxRigidActorExt::createExclusiveShape(*meshActor, geom, *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
		PhysxController::getInstance().addActor(meshActor);
	}
}

void TriangleMeshPhysicsComponent::Start() {
	PhysicsComponent::Start();
}

void TriangleMeshPhysicsComponent::Update() {
	PhysicsComponent::Update();
}
