#version 400 core
uniform sampler2D diffuseTex;

in Vertex 
{
	vec2 	texCoord;
	vec4 	color;
} IN;

out vec4 gl_FragColor;

void main(void)
{
	gl_FragColor = texture(diffuseTex, IN.texCoord);
	// gl_FragColor = vec4(IN.texCoord,1,1);
}