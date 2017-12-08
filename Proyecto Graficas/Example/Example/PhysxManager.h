#pragma once
#include <PxPhysicsAPI.h>
#include <vector>
#include "Matrix4D.h"

using namespace physx;

class PhysxManager
{
private:
	std::vector<PxRigidDynamic*> RigidBodies;
	float			gravity;
	float			size;

	PxFoundation *Foundation;
	PxPhysics *Physics;
	PxScene	*Scene;
	PxDefaultCpuDispatcher *Dispatcher;
	PxCudaContextManager *CudaContextManager;
	PxMaterial *Material;
	PxDefaultErrorCallback defaultErrorCallback;
	PxDefaultAllocator defaultAllocatorCallback;

public:
	void init();
	void update();
	void destroy();
	PxRigidDynamic* createCube(const PxTransform& trans);
	std::vector<Vector4D> getCubes();
	PhysxManager();
	~PhysxManager();
};

