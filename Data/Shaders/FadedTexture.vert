
attribute vec4 a_Position;
attribute vec2 a_UV;

uniform mat4 u_matWorld;
uniform mat4 u_matView;
uniform mat4 u_matProj;
uniform mat4 u_matNorm;

varying vec2 v_UV;

void main()
{
	vec4 modelpos = a_Position;
	vec4 worldpos = u_matWorld * modelpos; // apply world transform
	vec4 viewpos = u_matView * worldpos; // apply view transform
	vec4 finalpos = u_matProj * viewpos; // apply projection transform	

    gl_Position = finalpos;

	v_UV = a_UV;
}
