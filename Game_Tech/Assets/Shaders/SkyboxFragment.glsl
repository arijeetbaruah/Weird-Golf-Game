#version 150 core

uniform samplerCube cubeTexNight;
uniform vec3 cameraPos;
uniform float offsetX;
uniform float skyboxT;

vec4 colorLerp(vec4 from, vec4 to, float t)
{
	t = clamp(t, 0, 1);
	return (to - from) * t + from;
}

mat4 rotationY(in float angle) 
{
	return mat4(cos(angle), 0, sin(angle), 0,
			 	0, 1.0, 0, 0,
				-sin(angle), 0, cos(angle), 0,
				0, 0, 0, 1);
}

mat4 rotationX(in float angle) 
{
	return mat4(1.0, 0, 0, 0,
			 	0, cos(angle), -sin(angle), 0,
				0, sin(angle), cos(angle), 0,
				0, 0, 0, 1);
}

mat4 rotationZ(in float angle) 
{
	return mat4(cos(angle),-sin(angle),0,0,
			 	sin(angle),cos(angle),0,0,
				0,0,1,0,
				0,0,0,1);
}

in Vertex
{
    vec3 normal;
} IN;

out vec4 fragColor;
void main()
{
	vec4 nightColor = texture(cubeTexNight, normalize(vec4(IN.normal, 1.0) * rotationY(offsetX) * rotationX(offsetX / 2)).xyz);
	fragColor = colorLerp(vec4(0, 0, 0, 0), nightColor, skyboxT);
}