#include "CubeGL.h"
#include "Matrix4D.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#ifdef USING_D3DX
extern ComPtr<ID3D11Device>            D3D11Device;
extern ComPtr<ID3D11DeviceContext>     D3D11DeviceContext;
#endif

void CubeGL::Create() {
#ifdef USING_OPENGL_ES
	shaderID = glCreateProgram();

	char *vsSourceP = file2string("VS.glsl");
	char *fsSourceP = file2string("FS.glsl");

	GLuint vshader_id = createShader(GL_VERTEX_SHADER, vsSourceP);
	GLuint fshader_id = createShader(GL_FRAGMENT_SHADER, fsSourceP);

	glAttachShader(shaderID, vshader_id);
	glAttachShader(shaderID, fshader_id);

	glLinkProgram(shaderID);
	glUseProgram(shaderID);

	vertexAttribLoc = glGetAttribLocation(shaderID, "Vertex");
	normalAttribLoc = glGetAttribLocation(shaderID, "Normal");
	uvAttribLoc     = glGetAttribLocation(shaderID, "UV");

	matWorldViewProjUniformLoc = glGetUniformLocation(shaderID, "WVP");
	matWorldUniformLoc		   = glGetUniformLocation(shaderID, "World");
#elif defined(USING_D3D11)
	char *vsSourceP = file2string("VS.hlsl");
	char *fsSourceP = file2string("FS.hlsl");

	if (!vsSourceP || !fsSourceP)
		exit(32);

	HRESULT hr;
	{
		VS_blob = nullptr;
		ComPtr<ID3DBlob> errorBlob = nullptr;
		hr = D3DCompile(vsSourceP, (UINT)strlen(vsSourceP), 0, 0, 0, "VS", "vs_5_0", 0, 0, &VS_blob, &errorBlob);
		if (hr != S_OK) {

			if (errorBlob) {
				printf("errorBlob shader[%s]", (char*)errorBlob->GetBufferPointer());
				return;
			}

			if (VS_blob) {
				return;
			}
		}

		hr = D3D11Device->CreateVertexShader(VS_blob->GetBufferPointer(), VS_blob->GetBufferSize(), 0, &pVS);
		if (hr != S_OK) {
			printf("Error Creating Vertex Shader\n");
			return;
		}
	}

	{
		FS_blob = nullptr;
		ComPtr<ID3DBlob> errorBlob = nullptr;
		hr = D3DCompile(fsSourceP, (UINT)strlen(fsSourceP), 0, 0, 0, "FS", "ps_5_0", 0, 0, &FS_blob, &errorBlob);
		if (hr != S_OK) {
			if (errorBlob) {
				printf("errorBlob shader[%s]", (char*)errorBlob->GetBufferPointer());
				return;
			}

			if (FS_blob) {
				return;
			}
		}

		hr = D3D11Device->CreatePixelShader(FS_blob->GetBufferPointer(), FS_blob->GetBufferSize(), 0, &pFS);
		if (hr != S_OK) {
			printf("Error Creating Pixel Shader\n");
			return;
		}
	}

	free(vsSourceP);
	free(fsSourceP);
#endif
	// +Y SIDE
	vertices[0] = { -1.0f,  1.0f, -1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f };
	vertices[1] = {  1.0f,  1.0f, -1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f };
	vertices[2] = { -1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f };
	vertices[3] = {  1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f };

	// -Y SIDE
	vertices[4] = { -1.0f,  -1.0f, -1.0f, 1.0f,  0.0f, -1.0f, 0.0f, 1.0f,  1.0f, 0.0f };
	vertices[5] = {  1.0f,  -1.0f, -1.0f, 1.0f,  0.0f, -1.0f, 0.0f, 1.0f,  0.0f, 0.0f };
	vertices[6] = { -1.0f,  -1.0f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f, 1.0f,  1.0f, 1.0f };
	vertices[7] = {  1.0f,  -1.0f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f, 1.0f,  0.0f, 1.0f };

	// +X SIDE
	vertices[8]  = { 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f };
	vertices[9]  = { 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f };
	vertices[10] = { 1.0f, -1.0f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f };
	vertices[11] = { 1.0f, -1.0f, -1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f };

	// -X SIDE
	vertices[12] = { -1.0f,  1.0f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f };
	vertices[13] = { -1.0f,  1.0f, -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f };
	vertices[14] = { -1.0f, -1.0f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f };
	vertices[15] = { -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f };

	// +Z SIDE
	vertices[16] = { -1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f };
	vertices[17] = {  1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f };
	vertices[18] = { -1.0f, -1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f };
	vertices[19] = {  1.0f, -1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f };

	// -Z SIDE
	vertices[20] = { -1.0f,  1.0f, -1.0f, 1.0f,  0.0f, 0.0f, -1.0f, 1.0f,  1.0f, 0.0f };
	vertices[21] = {  1.0f,  1.0f, -1.0f, 1.0f,  0.0f, 0.0f, -1.0f, 1.0f,  0.0f, 0.0f };
	vertices[22] = { -1.0f, -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, -1.0f, 1.0f,  1.0f, 1.0f };
	vertices[23] = {  1.0f, -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, -1.0f, 1.0f,  0.0f, 1.0f };
#ifdef USING_OPENGL_ES
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(CVertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#elif defined(USING_D3D11)
	D3D11DeviceContext->VSSetShader(pVS.Get(), 0, 0);
	D3D11DeviceContext->PSSetShader(pFS.Get(), 0, 0);

	D3D11_INPUT_ELEMENT_DESC vertexDeclaration[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT,       0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = D3D11Device->CreateInputLayout(vertexDeclaration, ARRAYSIZE(vertexDeclaration), VS_blob->GetBufferPointer(), VS_blob->GetBufferSize(), &Layout);
	if (hr != S_OK) {
		printf("Error Creating Input Layout\n");
		return;
	}
	D3D11DeviceContext->IASetInputLayout(Layout.Get());

	D3D11_BUFFER_DESC bdesc = { 0 };
	bdesc.Usage = D3D11_USAGE_DEFAULT;
	bdesc.ByteWidth = sizeof(Cube::CBuffer);
	bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = D3D11Device->CreateBuffer(&bdesc, 0, pd3dConstantBuffer.GetAddressOf());
	if (hr != S_OK) {
		printf("Error Creating Buffer Layout\n");
		return;
	}

	D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());


	TextureD3D *texd3d = dynamic_cast<TextureD3D*>(tex);
	D3D11DeviceContext->PSSetShaderResources(0, 1, texd3d->pSRVTex.GetAddressOf());
	D3D11DeviceContext->PSSetSamplers(0, 1, texd3d->pSampler.GetAddressOf());


	bdesc = { 0 };
	bdesc.ByteWidth = sizeof(CVertex) * 24;
	bdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA subData = { vertices, 0, 0 };

	hr = D3D11Device->CreateBuffer(&bdesc, &subData, &VB);
	if (hr != S_OK) {
		printf("Error Creating Vertex Buffer\n");
		return;
	}

	bdesc = { 0 };
	bdesc.ByteWidth = 36 * sizeof(USHORT);
	bdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	subData = { indices, 0, 0 };

	hr = D3D11Device->CreateBuffer(&bdesc, &subData, &IB);
	if (hr != S_OK) {
		printf("Error Creating Index Buffer\n");
		return;
	}
#endif
	// +X
	indices[0] = 8;
	indices[1] = 9;
	indices[2] = 10;
	indices[3] = 9;
	indices[4] = 11;
	indices[5] = 10;

	// -X
	indices[6] = 14;
	indices[7] = 13;
	indices[8] = 12;
	indices[9] = 14;
	indices[10] = 15;
	indices[11] = 13;

	// +Y
	indices[12] = 1;
	indices[13] = 2;
	indices[14] = 0;
	indices[15] = 3;
	indices[16] = 2;
	indices[17] = 1;

	// -Y
	indices[18] = 4;
	indices[19] = 6;
	indices[20] = 5;
	indices[21] = 5;
	indices[22] = 6;
	indices[23] = 7;

	// +Z
	indices[24] = 17;
	indices[25] = 18;
	indices[26] = 16;
	indices[27] = 19;
	indices[28] = 18;
	indices[29] = 17;

	// -Z
	indices[30] = 20;
	indices[31] = 22;
	indices[32] = 21;
	indices[33] = 21;
	indices[34] = 22;
	indices[35] = 23;
#ifdef USING_OPENGL_ES
	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned short), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#elif defined(USING_D3D11)

#endif
	transform.myMatrix = Identity();
}

void CubeGL::Transform(float *t) {
	transform = t;
}

void CubeGL::Draw(float *t,float *vp) {
#ifdef USING_OPENGL_ES
	glUseProgram(shaderID);

	
	if (t)
		transform = t;

	Matrix VP;
	VP = vp;
	Matrix WVP;
	WVP.myMatrix = transform.myMatrix*VP.myMatrix;
	glUniformMatrix4fv(matWorldUniformLoc, 1, GL_FALSE, &transform.myMatrix.m[0][0]);
	glUniformMatrix4fv(matWorldViewProjUniformLoc, 1, GL_FALSE, &WVP.myMatrix.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glEnableVertexAttribArray(vertexAttribLoc);
	glEnableVertexAttribArray(normalAttribLoc);

	if (uvAttribLoc != -1) 
		glEnableVertexAttribArray(uvAttribLoc);
	
	glVertexAttribPointer(vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(0));
	glVertexAttribPointer(normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(16));
	
	if(uvAttribLoc!=-1)
		glVertexAttribPointer(uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(32));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(vertexAttribLoc);
	glDisableVertexAttribArray(normalAttribLoc);
	
	if (uvAttribLoc!=-1) {
	glDisableVertexAttribArray(uvAttribLoc);
	}
	glUseProgram(0);
#elif defined(USING_D3D11)
	if (t)
		transform = t;

	XMATRIX44 VP = XMATRIX44(vp);
	XMATRIX44 WVP = transform*VP;
	CnstBuffer.WVP = WVP;
	CnstBuffer.World = transform;

	UINT stride = sizeof(CVertex);
	UINT offset = 0;
	D3D11DeviceContext->VSSetShader(pVS.Get(), 0, 0);
	D3D11DeviceContext->PSSetShader(pFS.Get(), 0, 0);

	D3D11DeviceContext->IASetInputLayout(Layout.Get());

	D3D11DeviceContext->UpdateSubresource(pd3dConstantBuffer.Get(), 0, 0, &CnstBuffer, 0, 0);

	TextureD3D *texd3d = dynamic_cast<TextureD3D*>(tex);
	D3D11DeviceContext->PSSetShaderResources(0, 1, texd3d->pSRVTex.GetAddressOf());
	D3D11DeviceContext->PSSetSamplers(0, 1, texd3d->pSampler.GetAddressOf());

	D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());

	D3D11DeviceContext->IASetVertexBuffers(0, 1, VB.GetAddressOf(), &stride, &offset);
	D3D11DeviceContext->IASetIndexBuffer(IB.Get(), DXGI_FORMAT_R16_UINT, 0);

	D3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D11DeviceContext->DrawIndexed(36, 0, 0);
#endif
}

void CubeGL::Destroy() {
#ifdef USING_OPENGL_ES
	glDeleteProgram(shaderID);
#elif defined(USING_D3D11)

#endif
}

void CubeGL::SetDocName(char* docname)
{
}
