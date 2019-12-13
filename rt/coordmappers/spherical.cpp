#include <rt/coordmappers/spherical.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
{
    this->origin = origin;
    this->zeith = zenith;
    this->azimuthRef = azimuthRef;
}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    /* TODO */
    float scaleY = zeith.length();
    float scaleX = azimuthRef.length();
    Point p = hit.hitPoint();
    float r = sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
    float theta = std::atan2(p.y, p.x);
    float phi = acos(p.z / r);

    //TODO: you may not need r.
    float x, y, z;
    x = r * sin(phi) * cos(theta);
    y = r * sin(phi) * sin(theta);
    z = r * cos(phi);

    return (Point(scaleX * x, scaleY * y, z));

}

}