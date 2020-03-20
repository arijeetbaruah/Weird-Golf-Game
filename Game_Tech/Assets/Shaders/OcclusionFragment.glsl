#version 150 core

in Vertex 
{
	vec4 	color;
} IN;

out vec4 gl_FragColor;

void main(void)
{
	gl_FragColor = vec4(0.2, 1, 1, 0.7);
}