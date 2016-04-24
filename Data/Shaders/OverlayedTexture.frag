uniform sampler2D u_Texture;
uniform sampler2D u_SecondaryTexture;
uniform float u_ReflectionAmount;
uniform float u_Time;

varying vec4 v_WorldPosition;
varying vec3 v_Normal;

uniform vec3 u_LightPos[6];
uniform vec4 u_LightColor[6];
uniform vec3 u_CameraPosition;
varying vec2 v_UV;
void main()
{
    vec4 Color = texture2D( u_Texture, v_UV);
	vec4 ColorOverlay = texture2D(u_SecondaryTexture, v_UV + u_Time);
	float alpha = Color.w;
	if(alpha == 0.0f)
		discard;
	Color.xyz *= ColorOverlay.xyz;

		for(int i = 0; i < 6; i ++)
	{
		vec3 LightPos = u_LightPos[i];
		vec4 LightColor =  u_LightColor[i];
		vec3 NormVector = v_Normal;
		NormVector = normalize(NormVector);
		vec3 PixelPosition = v_WorldPosition.xyz;
		vec3 Position = LightPos - PixelPosition;
		float dist = distance(PixelPosition, LightPos) ;

		//diffuse
		vec3 LightDirection  = normalize(Position);
		float diffuseValue = dot(LightDirection, NormVector);
		if(diffuseValue < 0)
			diffuseValue = 0;
		vec4 diffuseColor = Color * LightColor;

		//specular
		vec3 camDir = u_CameraPosition - PixelPosition;
		camDir = normalize(camDir);
		vec3 halfVector = camDir + LightDirection;
		halfVector = normalize(halfVector);
		
		float specPercentage = dot(halfVector, NormVector);
		if(specPercentage < 0)
			specPercentage = 0;
		specPercentage = pow(specPercentage, 1000);
		vec4 specularColor = u_LightColor[i];

		diffuseColor.xyz /= (dist);
		float reflectionAmount = u_ReflectionAmount / (dist);
		gl_FragColor += ((diffuseColor * diffuseValue)
		+ ((specularColor * specPercentage) * reflectionAmount));
		
	}
	gl_FragColor.w = alpha;
}

