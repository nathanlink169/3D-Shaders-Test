uniform sampler2D u_Texture;
uniform float u_Time;
uniform bool u_On;
varying vec2 v_UV;

void main()
{
    vec4 Color = texture2D( u_Texture, v_UV );
	if(u_On == true)
	{
		//Static effect

		Color.x += sin(u_Time * 1);
		Color.y += cos(u_Time * 10);
	}
    gl_FragColor = Color;
}

