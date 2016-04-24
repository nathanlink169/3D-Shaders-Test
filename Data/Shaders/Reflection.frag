uniform sampler2D u_Texture;
uniform samplerCube u_CubeTexture;
uniform float u_ReflectionAmount;
uniform float u_ShineAmount;


varying vec4 v_WorldPosition;
varying vec3 v_Normal;
varying vec2 v_UV;

uniform vec3 u_LightPos[6];
uniform vec4 u_LightColor[6];
uniform vec3 u_CameraPosition;
void main()
{
	vec3 PixelPos = v_WorldPosition.xyz;
	vec3 Direction = PixelPos - u_CameraPosition;
	Direction = normalize(Direction);
	vec3 ReflecDir = reflect(Direction, v_Normal);
    vec4 Color = texture2D( u_Texture, v_UV);
	float alpha = Color.w;
	if(alpha == 0.0f)
		discard;
	vec4 ShineColor = textureCube(u_CubeTexture, ReflecDir);
	ShineColor *= u_ShineAmount;
	Color += ShineColor;

	gl_FragColor = Color;

	for(int i = 0; i < 6; i ++)
	{

		vec3 LightPos = u_LightPos[i];
		vec4 LightColor =  u_LightColor[i];
		vec3 NormVector = v_Normal;
		NormVector = normalize(NormVector);
		vec3 Position = LightPos - PixelPos;
		float dist = distance(PixelPos, LightPos) ;

		vec3 LightDirection  = normalize(Position);

		vec3 camDir = u_CameraPosition - PixelPos;
		camDir = normalize(camDir);
		vec3 halfVector = camDir + LightDirection;
		halfVector = normalize(halfVector);
		
		float specPercentage = dot(halfVector, NormVector);
		if(specPercentage < 0)
			specPercentage = 0;
		specPercentage = pow(specPercentage, 1000);
		vec4 specularColor = u_LightColor[i];

		float reflectionAmount = u_ReflectionAmount / (dist);
		gl_FragColor += ((specularColor * specPercentage) * reflectionAmount);
	}

	gl_FragColor.w = alpha;

}

