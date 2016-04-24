uniform sampler2D u_Texture;

varying vec2 v_UV;
void main()
{
    vec4 Color = texture2D( u_Texture, v_UV );
	float alpha = Color.w;
	if(alpha == 0.0f)
		discard;
    gl_FragColor = Color;
}

