#include "Application.h"
#include "BaseDriver.h"
#include "InputManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <PhysxManager.h>
#define NUM_LIGHTS 124
#define RADI 170.0f


float g_time;



void TestApp::InitVars() {
	DtTimer.Init();
	DtTimer.Update();
	g_time = 0;
	srand((unsigned int)DtTimer.GetDTSecs());
	Position = { 0.0f, 0.0f, 0.0f, 0.0f };
	Orientation = { 0.0f, 0.0f, 0.0f,0.0f };
	Scaling = {1.0f, 1.0f, 1.0f, 0};	
	Cam.Init(Vector4D{ 0.0f, 1.0f, 10.0f, 0.0f }, Deg2Rad(45.0f), 1280.0f / 720.0f, 1.0f, 8000.0f);
	Cam.Speed = 10.0f;
	Cam.Eye = Vector4D{ 0.0f, 9.75f, -31.0f, 0.0f };
	Cam.Pitch = 0.14f;
	Cam.Roll = 0.0f;
	Cam.Yaw = 0.020f;
	Cam.Update(0.0f);
	g_time = 0.0f;
	LightCam.Init(Vector4D{ 0.0f, 25.0f, -15.0f,0.0f }, Deg2Rad(60.0f), 1.0f, 0.1f, 8000.0f);
	LightCam.Speed = 10.0f;
	LightCam.Eye = Vector4D{ 0.0f, 35.0f, -40.0f,0.0f };
	LightCam.Pitch = 0.14f;
	LightCam.Roll = 0.0f;
	LightCam.Yaw = 0.020f;
	LightCam.Update(0.0f);

	ActiveCam = &Cam;
	sceneProps.AddCamera(ActiveCam);
	sceneProps.AmbientColor = { 0.55f, 0.55f, 0.55f,1.0f };
	sceneProps.AddLightCamera(&LightCam);
	for (int i = 0; i < NUM_LIGHTS; i++) {
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		sceneProps.AddLight(Vector4D{0.0f,25.0f,-35.0f} ,Vector4D{r,g,b,1.0f},true);
	}
	RTIndex = -1;
	FirstFrame = true;
	physxManager.init();
}

void TestApp::CreateAssets() {
	PrimitiveMgr.SetVP(&VP);
	int indexTri = PrimitiveMgr.CrateMeshGL((char*)"Scene.x",&sceneProps);
	int indexTri2 = PrimitiveMgr.CreateCube();
	int indexTri3 = PrimitiveMgr.CrateMeshGL((char*)"NuBatman.x", &sceneProps);
	int indexTri4 = PrimitiveMgr.CrateMeshGL((char*)"CerdoNuevo.x", &sceneProps);
	Cubes[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexTri2), &VP);
	Triangle[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexTri), &VP);
	Triangle1[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexTri3), &VP);
	Triangle2[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexTri4), &VP);
	Vector4D Pos = Vector4D{ 0.0f, 1.0f, -5.0f,0.0f };
	Vector4D Up = Vector4D{0.0f, 1.0f, 0.0f, 0.0};
	Vector4D LookAt = Vector4D{ 0.0001f, 0.0001f, 0.0001f,0.0f } -Pos;
	Cam.View = LookAtLH(Pos, LookAt, Up);
	Cam.Projection = PerspectiveFOVLH(Deg2Rad(45.0f), 1280.0f / 720.0f, 0.1f, 8000.0f);
	//D3DXMatrixOrthoRH(&Proj, 1280.0f / 720.0f, 1.0f , 0.1, 100.0f);
	Cam.VP = Cam.View*Cam.Projection;
}

void TestApp::DestroyAssets() {
	PrimitiveMgr.DestroyPrimitives();
	physxManager.destroy();
}

void TestApp::OnUpdate() {
	DtTimer.Update();
	Dtsecs = DtTimer.GetDTSecs();
	g_time += Dtsecs;
	OnInput();
	ActiveCam->Update(Dtsecs);
	VP = ActiveCam->VP;
	
	Triangle[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Triangle[0].RotateXAbsolute(Orientation.x);
	Triangle[0].RotateYAbsolute(Orientation.y);
	Triangle[0].RotateZAbsolute(Orientation.z);
	Triangle[0].ScaleAbsolute(Scaling.x);
	Triangle[0].Update();
	
	Triangle1[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Triangle1[0].RotateXAbsolute(Orientation.x);
	Triangle1[0].RotateYAbsolute(Orientation.y);
	Triangle1[0].RotateZAbsolute(Orientation.z);
	Triangle1[0].ScaleAbsolute(Scaling.x);
	Triangle1[0].Update();

	//Triangle2[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	
	Triangle2[0].TranslateAbsolute(sceneProps.Lights[0].Position.x, sceneProps.Lights[0].Position.y, sceneProps.Lights[0].Position.z);
	Triangle2[0].RotateXAbsolute(Orientation.x);
	Triangle2[0].RotateYAbsolute(Orientation.y);
	Triangle2[0].RotateZAbsolute(Orientation.z);
	Triangle2[0].ScaleAbsolute(Scaling.x);
	Triangle2[0].Update();

	Cubes[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Cubes[0].RotateXAbsolute(Orientation.x);
	Cubes[0].RotateYAbsolute(Orientation.y);
	Cubes[0].RotateZAbsolute(Orientation.z);
	Cubes[0].ScaleAbsolute(Scaling.x/10);
	Cubes[0].Update();

	float speed = 0.5f;
	static float freq = 0.0f;
	freq += Dtsecs*speed;
	static float freq2 = 3.1415f / 2.0f;
	freq2 += Dtsecs*speed;
	PrimitiveInst *Sel = &Triangle[5];
	Sel->TranslateAbsolute(Position.x, Position.y, Position.z);
	Sel->RotateXAbsolute(Orientation.x);
	Sel->RotateYAbsolute(Orientation.y);
	Sel->RotateZAbsolute(Orientation.z);
	Sel->ScaleAbsolute(Scaling.x);
	Sel->Update();
	physxManager.update();
	OnDraw();
}

void TestApp::OnDraw() {
	pFramework->pVideoDriver->Clear();
	Triangle[0].Draw();
	Triangle1[0].Draw();
	Triangle2[0].Draw();
	vector<Vector4D> Positions = physxManager.getCubes();
	for (int i = 0; i < Positions.size(); ++i) {
		Triangle2[0].TranslateAbsolute(Position.x, Position.y, Position.z);
		Triangle2[0].RotateXAbsolute(Orientation.x);
		Triangle2[0].RotateYAbsolute(Orientation.y);
		Triangle2[0].RotateZAbsolute(Orientation.z);
		Triangle2[0].ScaleAbsolute(Scaling.x *4.0f);
		Triangle2[0].TranslateRelative(Positions[i].x, Positions[i].y, Positions[i].z);
		Triangle2[0].Update();
		Triangle2[0].Draw();
	}
	pFramework->pVideoDriver->SwapBuffers();
	FirstFrame = false;
}

void TestApp::OnInput() {
	if (FirstFrame)
		return;

	bool changed = false;
	const float speedFactor = 5.0f;
	if (IManager.PressedKey(SDLK_DOWN)) {
		//Position.y += 1.0f*speedFactor*Dtsecs;
		sceneProps.Lights[0].Position.y -= 1.0f*speedFactor*Dtsecs;
		changed = true;
	}

	if (IManager.PressedKey(SDLK_UP)) {
		sceneProps.Lights[0].Position.y += 1.0f*speedFactor*Dtsecs;
		changed = true;
	}

	if (IManager.PressedKey(SDLK_RIGHT)) {
		sceneProps.Lights[0].Position.x += 1.0f*speedFactor*Dtsecs;
		changed = true;
	}

	if (IManager.PressedKey(SDLK_LEFT)) {
		sceneProps.Lights[0].Position.x -= 1.0f*speedFactor*Dtsecs;
		changed = true;
	}

	if (IManager.PressedKey(SDLK_x)) {
		sceneProps.Lights[0].Position.z -= 1.0f*speedFactor*Dtsecs;
		changed = true;
	}

	if (IManager.PressedKey(SDLK_z)) {
		sceneProps.Lights[0].Position.z += 1.0f*speedFactor*Dtsecs;
		changed = true;
	}

	if (IManager.PressedKey(SDLK_KP_PLUS)) {
		Scaling.x += 1.0f*DtTimer.GetDTSecs();
		Scaling.y += 1.0f*DtTimer.GetDTSecs();
		Scaling.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_MINUS)) {
		Scaling.x -= 1.0f*DtTimer.GetDTSecs();
		Scaling.y -= 1.0f*DtTimer.GetDTSecs();
		Scaling.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP5)) {
		Orientation.x -= 60.0f*speedFactor*Dtsecs;
		changed = true;
	}

	if (IManager.PressedKey(SDLK_KP6)) {
		Orientation.x += 60.0f*speedFactor*Dtsecs;
		changed = true;
	}

	if (IManager.PressedKey(SDLK_KP2)) {
		Orientation.y -= 60.0f*speedFactor*Dtsecs;
		changed = true;
	}

	if (IManager.PressedKey(SDLK_KP3)) {
		Orientation.y += 60.0f*speedFactor*Dtsecs;
		changed = true;
	}

	if (IManager.PressedKey(SDLK_KP0)) {
		Orientation.z -= 60.0f*speedFactor*Dtsecs;
		changed = true;
	}

	if (IManager.PressedKey(SDLK_KP_PERIOD)) {
		Orientation.z += 60.0f*speedFactor*Dtsecs;
		changed = true;
	}
	if (IManager.PressedKey(SDLK_w)) {
		ActiveCam->MoveForward(Dtsecs);
	}

	if (IManager.PressedKey(SDLK_s)) {
		ActiveCam->MoveBackward(Dtsecs);
	}

	if (IManager.PressedKey(SDLK_a)) {
		ActiveCam->StrafeLeft(Dtsecs);
	}

	if (IManager.PressedKey(SDLK_d)) {
		ActiveCam->StrafeRight(Dtsecs);
	}
	float yaw = 0.005f*static_cast<float>(IManager.xDelta);
	ActiveCam->MoveYaw(yaw);

	float pitch = 0.005f*static_cast<float>(IManager.yDelta);
	ActiveCam->MovePitch(pitch);
	if (IManager.PressedOnceKey(SDLK_SPACE)) {
		physxManager.createCube(PxTransform(Cam.Eye.x, Cam.Eye.y, Cam.Eye.z));
	}
}
void TestApp::OnPause() {

}

void TestApp::OnResume() {

}

void TestApp::OnReset() {

}