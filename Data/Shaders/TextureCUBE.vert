
attribute vec4 a_Position;

uniform mat4 u_matWorld;
uniform mat4 u_matView;
uniform mat4 u_matProj;

varying vec3 v_UV;

void main()
{
	vec4 modelpos = a_Position;
	vec4 worldpos = u_matWorld * modelpos; // apply world transform
	worldpos.w = 0;
	vec4 viewpos = u_matView * worldpos; // apply view transform
	viewpos.w = 1;
	vec4 finalpos = u_matProj * viewpos; // apply projection transform		
		
    gl_Position = finalpos;

	v_UV = a_Position.xyz;
}
