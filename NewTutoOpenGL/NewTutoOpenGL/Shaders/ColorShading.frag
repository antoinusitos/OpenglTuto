#version 130

in vec4 fragmentColor;

// the final color of the vertex
out vec4 color;

uniform float time;

void main()
{
	// get the color from the vertex shader
	color = fragmentColor + vec3(1.0 * (cos(time)+1.0) * 0.5, 1.0 * (cos(time + 2.0)+1.0) * 0.5, 1.0 * (sin(time)+1.0) * 0.5);
}