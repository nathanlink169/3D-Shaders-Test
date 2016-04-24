
uniform sampler2D u_Texture;

varying vec2 v_UV;
varying vec3 v_Position;
void main()
{
	vec4 color = texture2D( u_Texture, v_UV );
	color *= (v_Position.y + 1.5f);
	gl_FragColor = color;
}
