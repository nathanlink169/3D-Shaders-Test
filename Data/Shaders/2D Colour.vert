
attribute vec4 a_Position;

uniform mat4 u_matWorld;
uniform mat4 u_matProj;

void main()
{
	vec4 modelpos = a_Position;
	vec4 worldpos = u_matWorld * modelpos; // apply world transform
	vec4 finalpos = u_matProj * worldpos; // apply projection transform	

	vec2 finalPosition;
	finalPosition.x = finalpos.x;
	finalPosition.y = finalpos.y;	

    //gl_Position = finalpos;
	gl_Position = vec4(finalPosition, 0, 1);
}
