#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;


// inputs needed for 3D viewing
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = proj * view * model * vec4(aPos, 1.0);
}