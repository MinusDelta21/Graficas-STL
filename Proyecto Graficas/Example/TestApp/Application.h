#include <Core.h>
#include <PrimitiveManager.h>
#include <PrimitiveInstance.h>
#include "Matrix4D.h"
#include <Timer.h>
#include "Camera.h"
#include "SceneProps.h"
#include "PhysxManager.h"

class TestApp : public AppBase {
public:
	TestApp() : AppBase() {}
	void InitVars();
	void CreateAssets();
	void DestroyAssets();

	void OnUpdate();
	void OnDraw();
	void OnInput();

	void OnPause();
	void OnResume();

	void OnReset();
	SceneProps		sceneProps;
	PrimitiveManager PrimitiveMgr;
	PrimitiveInst	Cubes[10];
	PrimitiveInst	Triangle[10];
	PrimitiveInst	Triangle1[10];
	PrimitiveInst	Triangle2[10];
	CCamera Cam;
	CCamera *ActiveCam;
	CCamera LightCam;
	Vector4D		Position;
	Vector4D		Orientation;
	Vector4D		Scaling;
	Matrix4D		WorldTransform;

	Matrix4D		View;
	Matrix4D		Projection;
	Matrix4D		VP;

	bool	FirstFrame;
	Timer	DtTimer;
	float Dtsecs;
	int RTIndex;
	int CamSelection;
	Vector4D AmbientColor;
	PhysxManager physxManager;
};