#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 col;

uniform mat4 view;
uniform mat4 projection;
uniform int res;

void main()
{
    vec3 pos = (aPos / res) * 2 - 1;
    col = aPos / res;
    gl_Position = projection * view * vec4(pos, 1.0);
}