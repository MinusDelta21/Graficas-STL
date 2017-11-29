uniform mediump sampler2D Diffuse;
varying highp vec3 vecTransformed;
varying highp vec2 vecUVCoords;
varying highp vec4 vecPosition;
uniform highp vec4 LightPos;
void main()
{
	highp vec3 vecLight =  LightPos.xyz -vecPosition.xyz;
	vecLight = normalize(vecLight);
	highp vec3 normal = normalize(vecTransformed);

	highp vec3 DiffuseClr = texture2D(Diffuse,vecUVCoords).rgb;
	highp float Att = clamp(dot(vecLight,normal),0.0,1.0);

	highp vec3 Color = DiffuseClr;
	Color*=Att;
	Color += DiffuseClr * 0.30;

	gl_FragColor = vec4(Color,1.0);
}