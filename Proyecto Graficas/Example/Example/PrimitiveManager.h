#ifndef UAD_PRIMITIVEMANAGER_H
#define UAD_PRIMITIVEMANAGER_H

#include <vector>
#include <d3dx9math.h>
#include "Matrix4D.h"
#include "PrimitiveBase.h"
#include "MeshGl.h"
#include "SceneProps.h"


class PrimitiveManager {
public:
	void SetVP(Matrix4D *vp) {
		pVP = vp;
	}
	int  CreateTriangle();
	int	 CreateCube();
	int  CrateMeshGL(char* docname, SceneProps *props);
	void DrawPrimitives();
	void DestroyPrimitives();
	PrimitiveBase*	GetPrimitive(unsigned int);

	std::vector<PrimitiveBase*> primitives;

	Matrix4D *pVP;
};

#endif