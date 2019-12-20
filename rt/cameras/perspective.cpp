#include <rt/cameras/perspective.h>
#include<math.h>
#include <core/random.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float time0, float time1)
{
    this->center = center;
    this->forward = forward.normalize();
    this->up = up.normalize();
    this->horizontalOpeningAngle = horizontalOpeningAngle;
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->spanX = cross(forward, up).normalize();
    this->spanY = cross(spanX, forward).normalize();
    this->time0 = time0;
    this->time1 = time1;
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
    Vector d;
    x = x * tan(horizontalOpeningAngle/2);
    y = y * tan(verticalOpeningAngle/2);
    d = forward + x * spanX + y * spanY;
    d = d.normalize();
    float time = time0 + random()*(time1-time0);
    Ray primaryRay(center, d, time);
    return primaryRay;
}

}
