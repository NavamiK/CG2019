#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>
#include <cmath>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float focalDistance, float apertureRadius)
{
    /* TODO */
    this->center = center;
    this->forward = forward;
    this->up = up;
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->horizontalOpeningAngle = horizontalOpeningAngle;
    this->apertureRadius = apertureRadius;
    this->focalDistance = focalDistance;
}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
    /* TODO */
    float c = 0.025f; // coc
    float m = 1.f; // magnification.
    float N = 1.f; // lens number
    float dof = (2 * N *c ) / (m*m - (((N*c)/focalDistance)));

//    Vector d;
//    x = x * tan(horizontalOpeningAngle/2);
//    y = y * tan(verticalOpeningAngle/2);
//    d = focalDistance*forward + x * spanX + y * up;
//    d = d.normalize();
//    Ray primaryRay(center, d);
//    return primaryRay;
}

}