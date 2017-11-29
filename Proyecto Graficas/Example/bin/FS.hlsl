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
Texture2D TextureNormal : register(t1);

SamplerState SS;

struct VS_OUTPUT{
    float4 hposition : SV_POSITION;
	float4 hnormal   : NORMAL;
    float2 texture0  : TEXCOORD;
	float4 wPos		: TEXCOORD1;
};

float4 FS( VS_OUTPUT input ) : SV_TARGET  {
    float4 color;
	color *= Ambient;
	color = TextureRGB.Sample(SS, input.texture0);
	float4	LightDir = normalize(LightPos - input.wPos);
	float4  EyeDir = normalize(CameraPosition - input.wPos);
	float4	normal = normalize(input.hnormal);
	float4 DiffuseClr = TextureNormal.Sample(SS, input.texture0);
	DiffuseClr = DiffuseClr*float4(2.0, 2.0, 2.0,0.0) - float4(1.0, 1.0, 1.0,0.0);
	DiffuseClr = -DiffuseClr;
	DiffuseClr = normalize(DiffuseClr);
	normal = normalize(normal);
	float Att = clamp(dot(LightDir, normal), 0.0, 1.0);	
	color += DiffuseClr;
	color *= Att;
	color += DiffuseClr * 0.30;
		
    return color;
}
