
attribute vec4 a_Position;
attribute vec2 a_UV;
attribute vec3 a_Normal;
attribute vec4 a_Color;

uniform mat4 u_matWorld;
uniform mat4 u_matView;
uniform mat4 u_matProj;

void main()
{
	vec4 modelpos = a_Position;
	vec4 worldpos = u_matWorld * modelpos; // apply world transform
	vec4 viewpos = u_matView * worldpos; // apply view transform
	vec4 finalpos = u_matProj * viewpos; // apply projection transform		

    gl_Position = finalpos;
}
