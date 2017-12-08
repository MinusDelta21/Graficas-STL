cbuffer ConstantBuffer{
    float4x4 World;
    float4x4 WVP;
	float4	 LightPos;
	float4 	 LightColor;
	float4   CameraPosition;
	float4 	 CameraInfo;
	float4	 Ambient;
}

Texture2D TextureRGB : register(t0);

SamplerState SS;

struct VS_OUTPUT{
    float4 hposition : SV_POSITION;
	float4 hnormal   : NORMAL;
    float2 texture0  : TEXCOORD;
	float4 wPos		: TEXCOORD1;
};

float4 FS( VS_OUTPUT input ) : SV_TARGET  {
    float4 color;

	float4	LightDir = normalize(LightPos - input.wPos);
	float4  EyeDir = normalize(CameraPosition - input.wPos);
	float4	normal = input.hnormal;
	float4 DiffuseClr = TextureRGB.Sample(SS, input.texture0);
	float Att = clamp(dot(LightDir, normal), 0.0, 1.0);
	

	float4 SpecularClr = float4(1.0f, 1.0f, 1.0f, 1.0f);
	float specular = 0.0;
	float specIntesivity = 1.0;
	float gloss = 32.0;
	//PHONG

	float3 	ReflectedLight = reflect(-LightDir, normal);
	specular = max ( dot(ReflectedLight,EyeDir)/2 +0.5, -dot(ReflectedLight, EyeDir)/2+0.5);
	specular = pow(specular, gloss);

	//BLINN

	/*float3 ReflectedLight = normalize(EyeDir + LightDir);
	specular = max ( dot(ReflectedLight,normal)/2 +0.5, -0.6);
	specular = pow(specular, gloss);*/


	specular *= Att;
	specular *= specIntesivity;
	SpecularClr *= specular;

	color = (DiffuseClr + Ambient + SpecularClr)*Att;
    return color;
}
