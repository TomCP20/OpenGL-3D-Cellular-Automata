#include "OrbitCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

glm::vec3 OrbitCamera::getPos() const
{
    float x = radius * sin(polar) * cos(azimuthal);
    float y = radius * sin(polar) * sin(azimuthal);
    float z = radius * cos(polar);
    return glm::vec3(x, y, z);
}

OrbitCamera::OrbitCamera(float r, float p, float a)
{
    radius = r;
    polar = p;
    azimuthal = a;
}

void OrbitCamera::rotateAzimuth(const float angle)
{
    const float TAU = 2.0f * glm::pi<float>();
    azimuthal += angle;

    azimuthal = fmodf(azimuthal, TAU);
    if (azimuthal < 0)
    {
        azimuthal += TAU;
    }
}

void OrbitCamera::rotatePolar(const float angle)
{
    const float EPSILON = 0.001f;
    polar = std::clamp(polar + angle, EPSILON, glm::pi<float>() - EPSILON);
}

void OrbitCamera::zoom(const float delta)
{
    radius = std::max(0.1f, radius - delta);
}

glm::mat4 OrbitCamera::GetViewMatrix() const
{
    return glm::lookAt(getPos(), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
}
