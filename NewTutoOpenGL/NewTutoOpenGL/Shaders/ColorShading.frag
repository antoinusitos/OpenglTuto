#version 130

in vec4 fragmentColor;

out vec4 color;

void main()
{
	// get the color from the vertex shader
	color = fragmentColor;
}