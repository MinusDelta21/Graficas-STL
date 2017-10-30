#include "SceneProps.h"


void	SceneProps::AddLight(Vector4D Pos, Vector4D Color, bool enabled) {
	Light luz;
	luz.Position = Pos;
	luz.Color = Color;
	luz.Enabled = (int)enabled;
	Lights.push_back(luz);
}
void	SceneProps::RemoveLight(unsigned int index) {
	if (index < 0 || index >= Lights.size()) return;
	else Lights.erase(Lights.begin() + index);
}
void	SceneProps::SetLightPos(unsigned int index, Vector4D newPos) {
	if (index < 0 || index >= Lights.size())
		return;

	Lights[index].Position = newPos;
}
void	SceneProps::AddCamera(CCamera* cam) {
	pCameras.push_back(cam);
}
void	SceneProps::RemoveCamera(unsigned int index) {
	if (index < 0 || index >= pCameras.size())
		return;
	pCameras.erase(pCameras.begin() + index);
}
void	SceneProps::AddLightCamera(CCamera*cam) {
	pLightCameras.push_back(cam);

}
void	SceneProps::RemoveLightCamera(unsigned int index) {
	if (index < 0 || index >= pLightCameras.size())
		return;

	pLightCameras.erase(pLightCameras.begin() + index);
}
SceneProps::SceneProps()
{
	ActiveCamera = 0;
	ActiveLightCamera = 0;
	ActiveLights = 1;
}

SceneProps::~SceneProps()
{
}
