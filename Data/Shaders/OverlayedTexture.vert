
attribute vec4 a_Position;
attribute vec3 a_Normal;
attribute vec2 a_UV;

uniform mat4 u_matWorld;
uniform mat4 u_matView;
uniform mat4 u_matProj;
uniform mat4 u_matNorm;

varying vec2 v_UV;
varying vec3 v_Normal;
varying vec4 v_WorldPosition;

void main()
{
	vec4 modelpos = a_Position;
	vec4 worldpos = u_matWorld * modelpos; // apply world transform
	vec4 viewpos = u_matView * worldpos; // apply view transform
	vec4 finalpos = u_matProj * viewpos; // apply projection transform	

	// For Nathan's Computer - will try to comment this out before uploads
	vec4 nPos = u_matNorm * vec4(a_Normal,0);
	vec3 normalPos = vec3(nPos.x, nPos.y, nPos.z);

	// For everyone elses computer. Uncomment this if you're getting a shaders breakpoint
	//vec3 normalPos = u_matNorm * vec4(a_Normal,0);	

    gl_Position = finalpos;

	v_UV = a_UV;
	v_WorldPosition = worldpos;
	v_Normal = normalPos;
}
