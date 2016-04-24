
attribute vec4 a_Position;
attribute vec2 a_UV;

varying vec2 v_UV;

void main()
{
	vec4 finalpos = a_Position; 	
		
    gl_Position = finalpos;

	v_UV = a_UV;
}
