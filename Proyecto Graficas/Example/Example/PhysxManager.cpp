#include "PhysxManager.h"
using std::vector;

void PhysxManager::init()
{
	Foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, defaultAllocatorCallback, defaultErrorCallback);
	if (!Foundation) return;
	else {
		Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *Foundation, PxTolerancesScale(), 1);
		if (!Physics) return;
	}
	PxSceneDesc SceneDesc(Physics->getTolerancesScale());
	SceneDesc.gravity = PxVec3(0.0f, gravity, 0.0);
	Dispatcher = PxDefaultCpuDispatcherCreate(0);
	SceneDesc.cpuDispatcher = Dispatcher;
	SceneDesc.filterShader = PxDefaultSimulationFilterShader;
	Scene = Physics->createScene(SceneDesc);
	Material = Physics->createMaterial(0.5f, 0.5f, 0.5f);
	PxRigidStatic* Floor = PxCreatePlane(*Physics, PxPlane(0, 1, 0, 0), *Material);
	Scene->addActor(*Floor);

}

void PhysxManager::update()
{
	Scene->simulate(1.0f / 60.0f);
	Scene->fetchResults(true);
}

void PhysxManager::destroy()
{
	Scene->release();
	Dispatcher->release();
	Physics->release();
	Foundation->release();
}

PxRigidDynamic * PhysxManager::createCube(const PxTransform & trans)
{
	PxRigidDynamic* Box = PxCreateDynamic(*Physics, trans, PxBoxGeometry(4, 4, 4), *Material,10.0f);
	Box->setAngularDamping(0.5);
	Box->setLinearVelocity(PxVec3(15));
	Scene->addActor(*Box);
	RigidBodies.push_back(Box);
	return Box;
}

std::vector<Vector4D> PhysxManager::getCubes()
{
	vector<Vector4D>Positions;
	for (unsigned short s = 0; s < RigidBodies.size(); ++s) {
		Positions.push_back(Vector4D{ RigidBodies[s]->getGlobalPose().p.x, RigidBodies[s]->getGlobalPose().p.y, RigidBodies[s]->getGlobalPose().p.z });
	}
	return Positions;
}

PhysxManager::PhysxManager()
{
	gravity = -9.81f;
}


PhysxManager::~PhysxManager()
{
}
