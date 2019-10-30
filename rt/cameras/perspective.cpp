#include <rt/cameras/perspective.h>
#include<math.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
    /* TODO */
    this->center = center;
    this->forward = forward;
    this->up = up;
    this->horizontalOpeningAngle = horizontalOpeningAngle;
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->spanX = cross(forward, up);
    this->spanY = cross(forward, spanX);
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
    /* TODO */  
    Vector d;
    x = x * tan(horizontalOpeningAngle/2);
    y = y * tan(verticalOpeningAngle/2);
    d = forward + x * spanX + y * spanY;
    d = d.normalize(); 
    Ray primaryRay(center, d);
    return primaryRay;
}

}
