#ifndef UAD_GLDRIVER_H
#define UAD_GLDRIVER_H

#include "BaseDriver.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class GLDriver : public BaseDriver {
public:
	GLDriver() {  }
	void	InitDriver();
	void	CreateSurfaces();
	void	DestroySurfaces();
	void	Update();
	void	DestroyDriver();
	void	SetWindow(void *window);
	void	SetDimensions(int x, int y);
	void	Clear();
	void	SwapBuffers();

	EGLDisplay			eglDisplay;
	EGLConfig			eglConfig;
	EGLSurface			eglSurface;
	EGLContext			eglContext;

	EGLNativeWindowType	eglWindow;
	int 	 CreateTexture(std::string) { return 0; };
	Texture* GetTexture(int id) { Texture* x; return x; };
	void	 DestroyTexture() {};

	int 	 CreateRT(int nrt, int cf, int df, int w, int h) { return 0; };
	void	 PushRT(int id) {};
	void	 PopRT() {};
	void	 DestroyRT(int id) {};
	void	 DestroyRTs() {};
	Texture* GetRTTexture(int id, int index) { Texture* x; return x; };

	int			CreateShader(std::string src_vs, std::string src_fs, unsigned int sig) { return 0; };
	ShaderBase*	GetShaderSig(unsigned int sig) { ShaderBase* x; return x; };
	ShaderBase*	GetShaderIdx(int id) { ShaderBase* x; return x; };
	void		DestroyShaders() {};

	std::vector<ShaderBase*>	Shaders;
	std::vector<BaseRT*>		RTs;
	std::vector<Texture*>		Textures;
};

#endif