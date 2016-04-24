uniform sampler2D u_Texture;
uniform float u_Time;

varying vec2 v_UV;
void main()
{
    vec4 Color = texture2D( u_Texture, (v_UV + u_Time) );
	float alpha = Color.w / 2.0f;
	if(alpha == 0.0f)
		discard;
	Color.w /= 2.0f;
    gl_FragColor = Color;
}

