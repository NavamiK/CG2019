#include <rt/coordmappers/spherical.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
{
    this->origin = origin;
    this->zenith = zenith;
    this->azimuthRef = azimuthRef;
    this->radius = azimuthRef.length();
    this->scaleX = radius;
    this->scaleY = zenith.length();
    this->normal = cross(this->azimuthRef, this->zenith);
    //Cartesian to cylindrical coordinates
    this->rotM = Matrix::system(this->azimuthRef, this->zenith, normal).invert();
    this->transM = Matrix{
            Float4(1.f, 0.f, 0.f, origin.x),
            Float4(0.f, 1.f, 0.f, origin.y),
            Float4(0.f, 0.f, 1.f, origin.z),
            Float4(0.f, 0.f, 0.f, 1.f)
    }; 
    this->m = product(transM, rotM);

}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    /* TODO */
    /*float scaleY = zenith.length();
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
    return (Point(scaleX * x, scaleY * y, z)); */
    /*
    Point sphereT = m * hit.local();
    float theta = std::atan2(sphereT.z, sphereT.x);
    //float phi =  std::atan2(sphereT.x, sphereT.y * cos(theta));
    float phi = acos(sphereT.y / radius);
    float u = scaleX * theta / (2 * pi * scaleX);
    float v = scaleY * phi / pi;
   // float u = theta ;
    //float v = phi;
    return Point(u, v, 0.f);
    */
   Vector z = zenith;
   Vector aR = azimuthRef;
     Vector hitP=hit.local()-origin;
    Vector newPolar = (aR.normalize()- dot(aR.normalize(),z.normalize())*z).normalize();
    float y=(dot(hitP.normalize(),z.normalize())+1)/2;
    Vector hitP_Polar=(hitP- dot(hitP,z.normalize())*z).normalize();
    float x=(dot(hitP_Polar,newPolar)+1)/2;
    return Point (x,y,1);

}

}