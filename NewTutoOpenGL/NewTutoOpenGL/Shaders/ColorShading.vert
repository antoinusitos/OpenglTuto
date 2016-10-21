#version 130

// input data from the VBO. each vertex is two float
in vec2 vertexPosition; 

void main()
{
	// set the x,y position on the screen
	gl_Position.xy = vertexPosition;
	// the z position is zero since we are in 2D
	gl_Position.z = 0.0f;
	
	// indicates that the coordinates are normalized
	gl_Position.w = 1.0f;
}