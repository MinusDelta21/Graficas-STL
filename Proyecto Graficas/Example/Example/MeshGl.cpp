#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "MeshGl.h"
#include "Matrix4D.h"
#include <iostream>
#include <fstream>
#include <string>
#include "D3DXTexture.h"
using namespace std;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void MeshGL::SetDocName(char* docname) {
	docName = docname;
}
void MeshGL::setProps(SceneProps* props) {
	this->theProps = props;
}
void MeshGL::Create() {
	//Textures
#ifdef USING_OPENGL_ES
	shaderID = glCreateProgram();

	unsigned int glFiltering = 0;
	unsigned int glWrap = 0;

	glFiltering = GL_LINEAR_MIPMAP_LINEAR;
	glWrap = GL_CLAMP_TO_EDGE;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap);

	int Max = 1;
	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &Max);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Max);
	
	char *vsSourceP = file2string("VS_Mesh.glsl");
	char *fsSourceP = file2string("FS_Mesh.glsl");

	GLuint vshader_id = createShader(GL_VERTEX_SHADER, vsSourceP);
	GLuint fshader_id = createShader(GL_FRAGMENT_SHADER, fsSourceP);

	glAttachShader(shaderID, vshader_id);
	glAttachShader(shaderID, fshader_id);

	glLinkProgram(shaderID);
	glUseProgram(shaderID);

	vertexAttribLoc = glGetAttribLocation(shaderID, "Vertex");
	normalAttribLoc = glGetAttribLocation(shaderID, "Normal");
	uvAttribLoc = glGetAttribLocation(shaderID, "UV");

	matWorldViewProjUniformLoc = glGetUniformLocation(shaderID, "WVP");
	matWorldUniformLoc = glGetUniformLocation(shaderID, "World");
	DiffuseLoc = glGetUniformLocation(shaderID, "Diffuse");
	lightPosLoc = glGetUniformLocation(shaderID, "LightPos");
#elif defined(USING_D3D11)
	HRESULT hr;
	tex = new D3DXTexture;

	char *vsSourceP = file2string("VS.hlsl");
	char *fsSourceP = file2string("FS.hlsl");

	if (!vsSourceP || !fsSourceP)
		exit(32);


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

	//free(vsSourceP);
	//free(fsSourceP);

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
	bdesc.ByteWidth = sizeof(Buffers);
	bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = D3D11Device->CreateBuffer(&bdesc, 0, pd3dConstantBuffer.GetAddressOf());
	if (hr != S_OK) {
		printf("Error Creating Buffer Layout\n");
		return;
	}

	D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());


	D3DXTexture *texd3d = dynamic_cast<D3DXTexture*>(tex);
	D3D11DeviceContext->PSSetShaderResources(0, 1, texd3d->pSRVTex.GetAddressOf());
	D3D11DeviceContext->PSSetSamplers(0, 1, texd3d->pSampler.GetAddressOf());

	D3D11_SUBRESOURCE_DATA subData;

#endif


	//Read X File
	string line;
	int diffuseCount = 0;
	ifstream myfile;
	int numNormals, numTex, numMat;
	Matrix FTMr;
	Mesh *myMesh;
	unsigned short matPos = -1;
	myfile.open(docName);
	if (myfile.is_open())
	{
		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				char c_temp;
				if (line == "xof 0303txt 0032") cout << line << endl;
				int PosM = line.find("FrameTransformMatrix relative {");
				int PosV = line.find("Mesh mesh");
				int PosN = line.find("MeshNormals normals");
				int PosT = line.find("MeshTextureCoords tc");
				int PosMat = line.find("MeshMaterialList mtls {");
				int PosDif = line.find("diffuseMap");
				if (PosM != -1) {
					myfile >> FTMr.myMatrix.v[0] >> c_temp >> FTMr.myMatrix.v[1] >> c_temp >> FTMr.myMatrix.v[2] >> c_temp >> FTMr.myMatrix.v[3] >> c_temp >> FTMr.myMatrix.v[4] >> c_temp
						>> FTMr.myMatrix.v[5] >> c_temp >> FTMr.myMatrix.v[6] >> c_temp >> FTMr.myMatrix.v[7] >> c_temp >> FTMr.myMatrix.v[8] >> c_temp >> FTMr.myMatrix.v[9] >> c_temp
						>> FTMr.myMatrix.v[10] >> c_temp >> FTMr.myMatrix.v[11] >> c_temp >> FTMr.myMatrix.v[12] >> c_temp >> FTMr.myMatrix.v[13] >> c_temp >> FTMr.myMatrix.v[14] >> c_temp
						>> FTMr.myMatrix.v[15] >> c_temp >> c_temp;
				}
				if (PosV != -1) {
					myMesh = new Mesh;
					getline(myfile, line);
					myMesh->num_Vertices = stoi(line);
					cout << "Vertices: " << myMesh->num_Vertices << endl;
					//Separar vertices
					myMesh->vertices = new MeshVertex[myMesh->num_Vertices];
					for (int i = 0; i < myMesh->num_Vertices; i++) {
						myfile >> myMesh->vertices[i].x >> c_temp >> myMesh->vertices[i].y >> c_temp >> myMesh->vertices[i].z >> c_temp >> c_temp;
						myMesh->vertices[i].w = 1;
					}
					myfile >> myMesh->num_Indices >> c_temp;
					//n_Indices = myMesh->num_Indices;
					cout << "Indices: " << myMesh->num_Indices << endl;
					myMesh->indices = new unsigned short[myMesh->num_Indices * 3];
					for (int i = 0; i < myMesh->num_Indices; i++) {
						float aux;
						myfile >> aux >> c_temp;
						for (int j = 0; j < aux; j++) {
							myfile >> myMesh->indices[(i * 3) + j] >> c_temp;

						}
						myfile >> c_temp;
					}
				}
				if (PosN != -1) {
					getline(myfile, line);
					numNormals = stoi(line);
					cout << "Normals: " << numNormals << endl;
					//Separar vertices
					for (int i = 0; i < numNormals; i++) {
						myfile >> myMesh->vertices[i].nx >> c_temp >> myMesh->vertices[i].ny >> c_temp >> myMesh->vertices[i].nz >> c_temp >> c_temp;
						myMesh->vertices[i].nw = 1;
					}

				}
				if (PosT != -1) {
					getline(myfile, line);
					numTex = stoi(line);
					cout << "Texture: " << numTex << endl;
					//Separar vertices
					for (int i = 0; i < numTex; i++) {
						myfile >> myMesh->vertices[i].u >> c_temp >> myMesh->vertices[i].v >> c_temp >> c_temp;
					}
				}
				if (PosMat != -1) {
					getline(myfile, line);
					numMat = stoi(line);
					totalMat = numMat;
					cout << "Materials: " << numMat << endl;
					int numLineas;
					getline(myfile, line);
					numLineas = stoi(line);
					cout << "Lineas: " << numLineas << endl;
					std::streampos it_init = myfile.tellg();
					int temp;
					for (int i = 0; i < numMat; i++) {
						int matSize = 0;
						for (int j = 0; j < numLineas; ++j) {
							myfile >> temp >> c_temp;
							if (i == temp) {
								++matSize;
							}
						}
						myfile.seekg(it_init);
						myMesh->MaterialList.resize(numMat);
						myMesh->MaterialList[i].Contenedor = new unsigned short[matSize*3];
						myMesh->MaterialList[i].size = matSize * 3;
						int cont =0;
						for (int j = 0; j < numLineas; ++j) {
							myfile >> temp >> c_temp;
							if (i == temp) {
								myMesh->MaterialList[i].Contenedor[cont * 3] = myMesh->indices[j * 3];
								myMesh->MaterialList[i].Contenedor[(cont * 3)+1] = myMesh->indices[(j * 3)+1];
								myMesh->MaterialList[i].Contenedor[(cont * 3) + 2] = myMesh->indices[(j * 3) + 2];
							cont++;
							}
						}

						myfile.seekg(it_init);
					}

					Meshes.push_back(myMesh);

				}
					if (PosDif != -1) {
						
							myfile >> myMesh->MaterialList[diffuseCount].Path;
							myMesh->MaterialList[diffuseCount].Path = myMesh->MaterialList[diffuseCount].Path.substr(1, myMesh->MaterialList[diffuseCount].Path.size() - 3);
							cout << "Path: " << myMesh->MaterialList[diffuseCount].Path << endl;
							if (myMesh->MaterialList[diffuseCount].Path == ";") myMesh->MaterialList[diffuseCount].Path.erase();
							++diffuseCount;
					}
					if (diffuseCount == totalMat) {
						diffuseCount = 0;
						while (diffuseCount < numMat) {
		
							string path = "Textures/";
							path += myMesh->MaterialList[diffuseCount].Path;
							int x = 0, y = 0, channels = 0;
							unsigned char *buffer = stbi_load(path.c_str(), &x, &y, &channels, 0);
						#ifdef USING_OPENGL_ES
							glGenTextures(1, &myMesh->MaterialList[diffuseCount].TexID);
							glBindTexture(GL_TEXTURE_2D, myMesh->MaterialList[diffuseCount].TexID);

							glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

							glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)(buffer));
							glGenerateMipmap(GL_TEXTURE_2D);
						#elif defined(USING_D3D11)
						D3D11_TEXTURE2D_DESC desc = { 0 };
			desc.Width = x;
			desc.Height = y;
			desc.ArraySize = 1;			
			
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

			desc.SampleDesc.Count = 1;
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
			desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

			D3D11_SUBRESOURCE_DATA initData{};
			initData.pSysMem = buffer;
			initData.SysMemPitch = sizeof(unsigned char) * x * 4;

			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
			srvDesc.Format = desc.Format;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MipLevels = -1;

			D3D11Device->CreateTexture2D(&desc, nullptr, myMesh->MaterialList[diffuseCount].Tex.GetAddressOf());

			D3D11Device->CreateShaderResourceView(myMesh->MaterialList[diffuseCount].Tex.Get(), &srvDesc, myMesh->MaterialList[diffuseCount].pSRVTex.GetAddressOf());
			D3D11DeviceContext->UpdateSubresource(myMesh->MaterialList[diffuseCount].Tex.Get(), 0, 0, buffer, initData.SysMemPitch, 0);
			D3D11DeviceContext->GenerateMips(myMesh->MaterialList[diffuseCount].pSRVTex.Get());
						#endif
							++diffuseCount;
						}
						diffuseCount = 0;
					}
				
			}
			myfile.close();
		}
		else cout << "Unable to open file";
	}
	for (int i = 0; i < Meshes.size(); i++) {
		cout << Meshes[i]->vertices->u << ", " << Meshes[i]->vertices->v << endl;
	}
	Info.resize(Meshes.size());
	for (int i = 0; i < Meshes.size(); i++) {
		#ifdef USING_OPENGL_ES
			Info[i].num_Vertices = Meshes[i]->num_Vertices;
			Info[i].num_Indices = Meshes[i]->num_Indices;
			glGenBuffers(1, &Info[i].VB);
			glBindBuffer(GL_ARRAY_BUFFER, Info[i].VB);
			glBufferData(GL_ARRAY_BUFFER, Meshes[i]->num_Vertices * sizeof(MeshVertex), Meshes[i]->vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		#elif defined(USING_D3D11)
		Info[i].num_Vertices = Meshes[i]->num_Vertices;
		Info[i].num_Indices = Meshes[i]->num_Indices;
		bdesc = { 0 };
		bdesc.ByteWidth = sizeof(MeshVertex) * Info[i].num_Vertices;
		bdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		subData = { Meshes[i]->vertices, 0, 0 }; // -->

		hr = D3D11Device->CreateBuffer(&bdesc, &subData, &Info[i].VB);
		if (hr != S_OK) {
			printf("Error Creating Vertex Buffer\n");
			myfile.close();															// Finish 
			return;
		}

		#endif
			for (int j = 0; j < Meshes[i]->MaterialList.size(); ++j) {
			#ifdef USING_OPENGL_ES

				glGenBuffers(1, &Meshes[i]->MaterialList[j].IB);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Meshes[i]->MaterialList[j].IB);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, Meshes[i]->MaterialList[j].size  * sizeof(unsigned short), Meshes[i]->MaterialList[j].Contenedor, GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			#elif defined(USING_D3D11)
				
				bdesc = { 0 };
				bdesc.ByteWidth = Meshes[i]->MaterialList[j].size * sizeof(unsigned short);
				bdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

				subData = { Meshes[i]->MaterialList[j].Contenedor, 0, 0 };

				hr = D3D11Device->CreateBuffer(&bdesc, &subData, &Meshes[i]->MaterialList[j].IB);
				if (hr != S_OK) {
					printf("Error Creating Index Buffer\n");
					myfile.close();													// Finish 
					return;
				}
			#endif
			}
		
	}
	transform.myMatrix = Identity();
}

void MeshGL::Transform(float *t) {
	transform = t;
}

void MeshGL::Draw(float *t, float *vp) {
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
	//Vector4D LightPos = Vector4D{ 5,0,0 };
 	glUniform4fv(lightPosLoc, 1, &theProps->Lights[0].Position.v[0]);
	for (int i = 0; i < Meshes.size(); i++) {

		glBindBuffer(GL_ARRAY_BUFFER, Info[i].VB);
		glEnableVertexAttribArray(vertexAttribLoc);
		if (normalAttribLoc != -1)
			glEnableVertexAttribArray(normalAttribLoc);

		if (uvAttribLoc != -1)
			glEnableVertexAttribArray(uvAttribLoc);

		glVertexAttribPointer(vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(0));
		if (normalAttribLoc != -1)
			glVertexAttribPointer(normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(16));

		if (uvAttribLoc != -1)
			glVertexAttribPointer(uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), BUFFER_OFFSET(32));


		for (int j = 0; j < Meshes[i]->MaterialList.size(); ++j) {
			if (DiffuseLoc != -1) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, Meshes[i]->MaterialList[j].TexID);
				glUniform1i(DiffuseLoc, 0);
			}
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Meshes[i]->MaterialList[j].IB);
			glDrawElements(GL_TRIANGLES, Meshes[i]->MaterialList[j].size * 3, GL_UNSIGNED_SHORT, 0);

		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(vertexAttribLoc);
		if (normalAttribLoc != -1)
			glDisableVertexAttribArray(normalAttribLoc);

		if (uvAttribLoc != -1) {
			glDisableVertexAttribArray(uvAttribLoc);
		}
	}
	#elif defined(USING_D3D11)
	if (t)
		transform = t;

	Matrix VP;
	VP = vp;
	Matrix WVP;
	WVP.myMatrix = transform.myMatrix*VP.myMatrix;

	CnstBuffer.WVP = WVP.myMatrix;
	CnstBuffer.World = transform.myMatrix;
	//Asignar posicion de luz
	CnstBuffer.Light0Pos = theProps->Lights[0].Position;
	//Asignar color de luz
	CnstBuffer.Light0Col = theProps->Lights[0].Color;
	//Asignar posicion de la camara
	CnstBuffer.CameraPos = theProps->pCameras[0]->Eye;
	//Asignar ambient color
	CnstBuffer.Ambient = theProps->AmbientColor;


	UINT stride = sizeof(MeshVertex);
	UINT offset = 0;
	D3D11DeviceContext->VSSetShader(pVS.Get(), 0, 0);
	D3D11DeviceContext->PSSetShader(pFS.Get(), 0, 0);
	D3D11DeviceContext->IASetInputLayout(Layout.Get());
	D3D11DeviceContext->UpdateSubresource(pd3dConstantBuffer.Get(), 0, 0, &CnstBuffer, 0, 0);
	D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	
	
	for (int i = 0; i < Meshes.size(); i++) {
		D3D11DeviceContext->IASetVertexBuffers(0, 1, Info[i].VB.GetAddressOf(), &stride, &offset);
		for (int j = 0; j < Meshes[i]->MaterialList.size(); ++j) {			
			D3D11DeviceContext->PSSetShaderResources(0, 1, Meshes[i]->MaterialList[j].pSRVTex.GetAddressOf());
			D3D11DeviceContext->PSSetSamplers(0, 1, Meshes[i]->MaterialList[j].pSampler.GetAddressOf());
			D3D11DeviceContext->IASetIndexBuffer(Meshes[i]->MaterialList[j].IB.Get(), DXGI_FORMAT_R16_UINT, 0);
			D3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			D3D11DeviceContext->DrawIndexed(Meshes[i]->MaterialList[j].size, 0, 0);
		}
	}

	#endif

#ifdef USING_OPENGL_ES
	glUseProgram(0);
#elif defined(USING_D3D11)

#endif
}

void MeshGL::Destroy() {
#ifdef USING_OPENGL_ES
	glDeleteProgram(shaderID);
#elif defined(USING_D3D11)

#endif
}