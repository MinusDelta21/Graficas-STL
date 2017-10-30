#pragma once
#include"Camera.h"
#include"Matrix4D.h"
#include <vector>
using std::vector;

struct Light{
	Vector4D Position;
	Vector4D Color;
	int Type;
	int Enabled;
};

class SceneProps
{
public:
	vector<Light>		Lights;
	vector<CCamera*>	pCameras;
	vector<CCamera*>	pLightCameras;
	Vector4D			AmbientColor;
	int					ActiveCamera;
	int					ActiveLights;
	int					ActiveLightCamera;
	void				AddLight(Vector4D Pos, Vector4D Color, bool enabled);
	void				RemoveLight(unsigned int index);
	void				SetLightPos(unsigned int index, Vector4D newPos);
	void				AddCamera(CCamera*cam);
	void				RemoveCamera(unsigned int index);
	void				AddLightCamera(CCamera*);
	void				RemoveLightCamera(unsigned int index);
	SceneProps();
	~SceneProps();
};

