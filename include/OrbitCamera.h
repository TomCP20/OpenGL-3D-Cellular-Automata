#ifndef ORBIT_CAMERA_H
#define ORBIT_CAMERA_H

#include <glm/glm.hpp>

const float ZOOM = 45.0f;

class OrbitCamera
{
private:
    float radius;
    float polar;
    float azimuthal;

    glm::vec3 getPos() const;
public:
    OrbitCamera(float r, float p, float a);

    void rotateAzimuth(const float angle);
    void rotatePolar(const float angle);
    void zoom(const float delta);

    glm::mat4 GetViewMatrix() const;
};

#endif