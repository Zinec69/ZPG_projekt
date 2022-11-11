#version 330

in vec3 TexCoords;

out vec4 FragColor;

uniform samplerCube SkyBox;

void main()
{
    FragColor = texture(SkyBox, TexCoords);
}
