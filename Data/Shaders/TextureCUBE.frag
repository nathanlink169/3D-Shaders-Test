uniform samplerCube u_CubeTexture;
varying vec3 v_UV;

void main()
{
    vec4 Color = textureCube( u_CubeTexture, v_UV );
    gl_FragColor = Color;
}

