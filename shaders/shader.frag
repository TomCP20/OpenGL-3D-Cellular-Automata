#version 330 core
out vec4 FragColor;

in vec3 col;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = vec4(col, 1.0);
}