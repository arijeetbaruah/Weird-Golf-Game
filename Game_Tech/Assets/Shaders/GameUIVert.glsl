#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;

uniform vec4 		objectColour = vec4(1,1,1,1);

out Vertex
{
	vec4 colour;
} OUT;

void main(void)
{
	gl_Position		= position;
}