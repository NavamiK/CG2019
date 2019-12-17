#include <rt/coordmappers/spherical.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
{
    this->origin = origin;
    this->z = zenith;
    this->aR = azimuthRef;
    //this->radius = azimuthRef.length();
    this->scaleX = aR.length();
    this->scaleY = z.length();
}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    /* TODO */

    Vector hitP = hit.local()-origin;
    //Angle between of hitP and zenith
    float v = acos(dot(z.normalize(),hitP.normalize()));  

    //Remove the component of aR along z, to make z orthogonal to aR
    Vector perpPolar = (aR - dot(z.normalize(),aR)*z);
   
    //Project hitP onto the plane perpendicular to lA, & containing origin
    Vector polarHit = (hitP -  dot(z.normalize(),hitP)* z).normalize();

    //phi in the plane between new polar axis and projector vector
    float u = acos(dot(polarHit, perpPolar));
    return Point(u,v,0);
}

}