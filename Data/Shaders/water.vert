
attribute vec4 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform mat4 u_matWorld;
uniform mat4 u_matView;
uniform mat4 u_matProj;

varying vec3 v_Position;

uniform float u_Time;
uniform float u_rippleSize;

uniform vec3 u_RipplePositions[50];
uniform int u_RippleActive[50];
uniform float u_RippleDecay[50];
uniform float u_RippleMaxRadius[50];
uniform float u_RippleMinRadius[50];
uniform float u_RippleSinTime[50];


varying vec2 v_UV;

void main()
{
	vec4 modelpos = a_Position;

	//Gavin's Waves
	//modelpos.y += sin(modelpos.x * 5 + u_Time * 2) / 40.0f;
	//modelpos.y += sin(modelpos.z * 2 + u_Time * 7) / 25.0f;

	//marks ripples :D
	//ripple effect (takes the distance between the various ripple points and creates a sinewave that fades based on distance and time)

	vec4 worldpos = u_matWorld * modelpos; // apply world transform

	for(int i = 0; i < 50; i ++)
	{
        if(u_RippleActive[i] == 1)
		{
            float dist = sqrt((worldpos.x - u_RipplePositions[i].x) * (worldpos.x -u_RipplePositions[i].x) + (worldpos.y -u_RipplePositions[i].y)
			* (worldpos.y - u_RipplePositions[i].y) + (worldpos.z - u_RipplePositions[i].z) * (worldpos.z -u_RipplePositions[i].z));
			if(dist <= u_RippleMaxRadius[i] && dist >= u_RippleMinRadius[i])
			{
				worldpos.y += (sin(dist - (u_RippleSinTime[i] * 5)) / (dist + /* offset dist so we dont get peeks */ u_RippleDecay[i])) * u_rippleSize;
			}
        }
	}

	vec4 viewpos = u_matView * worldpos; // apply view transform
	vec4 finalpos = u_matProj * viewpos; // apply projection transform		

    gl_Position = finalpos;
	v_UV = a_UV;
	v_Position = vec3(worldpos.x, worldpos.y, worldpos.z);
}
