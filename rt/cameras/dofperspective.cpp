#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>
#include <cmath>
#include <core/random.h>

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

//References
//https://medium.com/@elope139/depth-of-field-in-path-tracing-e61180417027
//https://www.scratchapixel.com/lessons/3d-basic-rendering/3d-viewing-pinhole-camera

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
    /* TODO */
    Vector d;
    x = x * tan(horizontalOpeningAngle/2);
    y = y * tan(verticalOpeningAngle/2);
    d = forward + x * spanX + y * spanY;
    d = d.normalize();

    Point focalPoint = center + focalDistance * d; 
    float r = random(); float s = random(); float t = random(); float u  = random();
    if(r < 0.5)
        s = -s;
    if(t < 0.5)
        u = -u;
    Point rayOrigin = center + s * apertureRadius * spanX + u * apertureRadius * spanY;
    Vector rayDirection = (focalPoint - rayOrigin).normalize();

    float time = time0 + random()*(time1-time0);
    
    Ray primaryRay(rayOrigin, rayDirection, time);
    return primaryRay;
}

}