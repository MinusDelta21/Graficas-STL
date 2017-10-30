#ifndef UAD_MESH_GL_H
#define UAD_MESH_GL_H
#include "Config.h"
#include <D3Dcompiler.h>
#include <d3dx9math.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <d3dx9math.h>
#include "Matrix4D.h"
#include "PrimitiveBase.h"
#include "UtilsGL.h"
#include <string>
#include <fstream>
#include <vector>
#include <d3d11.h>
#include <wrl.h>
#include <wrl/client.h>
#include "Textures.h"
#include "D3DXTexture.h"

using namespace std;
using namespace Microsoft::WRL;
//using namespace xF;
extern ComPtr<ID3D11Device>            D3D11Device;
extern ComPtr<ID3D11DeviceContext>     D3D11DeviceContext;
struct MeshVertex {
	float x, y, z, w;
	float nx, ny, nz, nw;
	float u, v;
};
struct Material {
#ifdef USING_OPENGL_ES
	GLuint TexID;
	GLuint IB;
#elif defined(USING_D3D11)
	ComPtr<ID3D11Texture2D>				Tex;
	ComPtr<ID3D11ShaderResourceView>    pSRVTex;
	ComPtr<ID3D11SamplerState>          pSampler;
	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;

	
#endif
	int size;
	unsigned short *Contenedor;
	string Path;
};
struct CTexture {
#ifdef USING_OPENGL_ES
	GLuint TexID;
#elif defined(USING_D3D11)
	
	
#endif
	int x, y, channels;
};
struct Mesh
{
	MeshVertex			*vertices;
	unsigned short		*indices;
	int num_Vertices;
	int num_Indices;
	vector<Material> MaterialList;
	vector<CTexture>Textures;
	ComPtr<ID3D11Buffer>		VB;
};

struct Buffers {
#ifdef USING_OPENGL_ES
	GLuint			VB;
	GLuint			IB;
	int num_Vertices;
	int num_Indices;
#elif defined(USING_D3D11)
	
	Matrix4D WVP;
	Matrix4D World;
	Vector3  Light0Pos;
	Vector3  Light0Col;
	Vector3  CameraPos;
	Vector3  Ambient;
	
	
#endif
};

class MeshGL : public PrimitiveBase {
public:
	void Create();
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();
	void SetDocName(char* docname);
	void setProps(SceneProps* props);
	char* docName;
	vector<Buffers> Info;
	GLint DiffuseLoc;
	SceneProps *theProps;
	Matrix transform;
	int totalMat;
	vector<Mesh*> Meshes;
	Texture		*tex;
#ifdef USING_OPENGL_ES
	MeshGL() : shaderID(0) {}
	GLuint	shaderID;
	GLint	vertexAttribLoc;
	GLint lightPosLoc;
	GLint	normalAttribLoc;
	GLint	uvAttribLoc;
	GLint  matWorldViewProjUniformLoc;
	GLint  matWorldUniformLoc;
#elif defined(USING_D3D11)
	ComPtr<ID3D11VertexShader>  pVS;
	ComPtr<ID3D11PixelShader>   pFS;
	ComPtr<ID3DBlob>            VS_blob;
	ComPtr<ID3DBlob>            FS_blob;
	ComPtr<ID3D11InputLayout>   Layout;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;

	std::vector<D3D11_INPUT_ELEMENT_DESC>	VertexDecl;

	Buffers				CnstBuffer;
#endif
};


#endif