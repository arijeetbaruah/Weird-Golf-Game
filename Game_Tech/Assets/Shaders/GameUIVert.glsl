#version 400 core

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projMatrix = mat4(1.0f);

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;

uniform vec4 		objectColour = vec4(1,1,1,1);

out Vertex
{
	vec4 colour;
} OUT;

void main(void)
{
	mat4 mvp = (projMatrix * viewMatrix * modelMatrix);
	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));

	gl_Position = mvp * vec4(position, 1.0);
}