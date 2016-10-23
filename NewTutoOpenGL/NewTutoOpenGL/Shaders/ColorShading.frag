#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;

// the final color of the vertex
out vec4 color;

uniform float time;

void main()
{
	// get the color from the vertex shader
	color = vec4(fragmentColor.r * (cos(fragmentPosition.x * 8.0 + time) + 1.0) *0.5,
				 fragmentColor.g * (cos(fragmentPosition.y * 8.0  + time) + 1.0) *0.5,
				 fragmentColor.b * (cos(fragmentPosition.x * 2.0 + time) + 1) *0.5,
				 fragmentColor.a);
}	