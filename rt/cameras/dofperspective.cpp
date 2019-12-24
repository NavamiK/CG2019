#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>
#include <cmath>
#include <core/scalar.h>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float focalDistance, float apertureRadius, float time0, float time1)
{
    /* TODO */
    this->center = center;
    this->forward = forward;
    this->up = up;
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->horizontalOpeningAngle = horizontalOpeningAngle;
    this->apertureRadius = apertureRadius;
    this->focalDistance = focalDistance;

    this->spanX = cross(forward, up).normalize();
    this->spanY = cross(spanX, forward).normalize();
    this->time0 = time0;
    this->time1 = time1;

}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
    /* TODO */
    //formula from:
    //https://en.wikipedia.org/wiki/Circle_of_confusion
    float c = pi * apertureRadius * apertureRadius; // coc
    float m = 1.f; // magnification.
    float N = 1.f;//focalDistance/(apertureRadius*apertureRadius); // TODO: replace by 1.f later. lens number
    //float dof = (2 * N *c ) / (m*m - (((N*c)/focalDistance)));
    float dof = apertureRadius/focalDistance;

    Vector d;
    x = x * tan(horizontalOpeningAngle/2);
    y = y * tan(verticalOpeningAngle/2);
    d = forward + dof * x * spanX + dof * y * spanY;
    d = d.normalize();
    float time = time0 + random()*(time1-time0);
    Ray primaryRay(center, d, time);
    return primaryRay;
}

}