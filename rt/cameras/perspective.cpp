#include <rt/cameras/perspective.h>
#include<math.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
    this->center = center;
    this->forward = forward;
    this->up = up;
    this->horizontalOpeningAngle = horizontalOpeningAngle;
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->spanX = cross(forward, up).normalize();
    //this->spanY = cross(forward, spanX); //this computation for the exact images in A01
    this->spanY = cross(spanX, forward).normalize();
    
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
    Vector d;
    x = x * tan(horizontalOpeningAngle/2);
    y = y * tan(verticalOpeningAngle/2);
    d = forward + x * spanX + y * spanY;
    d = d.normalize(); 
    Ray primaryRay(center, d);
    return primaryRay;
}

}
