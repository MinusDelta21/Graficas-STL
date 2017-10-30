#ifndef UAD_CUBE_GL_H
#define UAD_CUBE_GL_H
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <d3dx9math.h>
#include "Matrix4D.h"
#include "PrimitiveBase.h"
#include "UtilsGL.h"



struct CVertex {

	float x, y, z,w;
	float nx,ny,nz,nw;
	float s,t;
};


class CubeGL : public PrimitiveBase {
public:
	CubeGL()
#ifdef USING_OPENGL_ES
		: shaderID(0)
#endif
	{}
	void Create();
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();
	void setProps(SceneProps* props) {};
	void SetDocName(char* docname);
	unsigned short	indices[36];
	CVertex			vertices[24];
	Matrix transform;

#ifdef USING_OPENGL_ES
	GLuint	shaderID;
	GLint	vertexAttribLoc;
	GLint	normalAttribLoc;
	GLint	uvAttribLoc;

	GLint  matWorldViewProjUniformLoc;
	GLint  matWorldUniformLoc;

	GLuint			VB;
	GLuint			IB;
#elif defined(USING_D3D11)
	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;
	ComPtr<ID3D11VertexShader>  pVS;
	ComPtr<ID3D11PixelShader>   pFS;
	ComPtr<ID3DBlob>            VS_blob;
	ComPtr<ID3DBlob>            FS_blob;
	ComPtr<ID3D11InputLayout>   Layout;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;

	Buffers	CnstBuffer;
#endif
};
#endif