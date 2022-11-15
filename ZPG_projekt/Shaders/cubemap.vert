#version 330

layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;
uniform float scale;

out vec3 TexCoords;

void main()
{
	 TexCoords = aPos * scale;
	 gl_Position = projection * mat4(mat3(view)) * vec4(TexCoords, 1.0);
}
