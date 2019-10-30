#include <rt/cameras/orthographic.h>
#include <rt/ray.h>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY)
{
    /* TODO */
    this->center = center;
    this->forward = forward;
    this->up = up;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
    /* TODO */ 
    // Generate direction through pixel center
    Vector d;
    Vector spanX(scaleX, 0.0f, 0.0f);
    Vector spanY(0.0f,scaleY, 0.0f);
    d = forward + x * spanX + y * spanY;
    d = d.normalize(); // May normalize here
    Ray primaryRay(center, d);
    return primaryRay;
}

}
