#include <rt/cameras/perspective.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
    /* TODO */
    this->center = center;
    this->forward = forward;
    this->up = up;
    this->horizontalOpeningAngle = horizontalOpeningAngle;
    this->verticalOpeningAngle = verticalOpeningAngle;
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
    /* TODO */  // Generate direction through pixel center
    Vector d;
    Vector spanX(horizontalOpeningAngle, 0.0f, 0.0f);
    Vector spanY(0.0f,verticalOpeningAngle, 0.0f);
    d = forward + x * spanX + y * spanY;
    d = d.normalize(); // May normalize here
    Ray primaryRay(center, d);
    return primaryRay;
}

}
