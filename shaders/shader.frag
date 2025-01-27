#version 330 core
out vec4 FragColor;

in vec3 col;

vec3 Quantization(float n, vec3 col)
{
    return floor(col * n) / (n - 1.0);
}

void main()
{
    FragColor = vec4(Quantization(16, col), 1.0);
}