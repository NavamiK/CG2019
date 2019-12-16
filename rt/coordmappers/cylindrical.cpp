#include <rt/coordmappers/cylindrical.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
{
    /* TODO need to clean up*/ 
    this->origin = origin;
    this->longitudinalAxis = longitudinalAxis;
    this->polarAxis = polarAxis;
    this->height = longitudinalAxis.length();
    this->scaleX = polarAxis.length();
    this->normal = cross(this->polarAxis, this->longitudinalAxis);
    //Cartesian to cylindrical coordinates
    this->rotM = Matrix::system(this->polarAxis, normal, this->longitudinalAxis).invert();
    this->transM = Matrix{
            Float4(1.f, 0.f, 0.f, origin.x),
            Float4(0.f, 1.f, 0.f, origin.y),
            Float4(0.f, 0.f, 1.f, origin.z),
            Float4(0.f, 0.f, 0.f, 1.f)
    }; 
    this->cartToCylM = product(transM, rotM);
    //this->cartToCylM = product(rotM, transM);

}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    /* TODO */ 
    //Point hLocal = m * hit.local();
    //float phi = std::atan2(hLocal.y, hLocal.x);
    //if (phi < 0) phi += 2 * pi;
    
   // Point cylindricalT = cartToCylM * hit.local();
   // float phi = std::atan2(cylindricalT.y, cylindricalT.x);
   // if (phi < 0) phi += 2 * pi;
    //float u = phi;
    //float u = phi;
   // float v = cylindricalT.z;
    //return Point(u, v, 0.f);
    
   Vector lA = longitudinalAxis;
   Vector pA = polarAxis;
     Vector newPolar = (pA.normalize()- dot(lA.normalize(),pA.normalize())*lA).normalize();
    Vector hitP=hit.hitPoint()-origin;
    float y= dot(lA.normalize(),hitP)/lA.length();  // works better than v
    //float y= 2*dot(lA,hitP);
    Vector polarHit=(hitP- dot(lA.normalize(),hitP)*lA.normalize()).normalize();
    float x=(dot(polarHit,newPolar)) * pA.length();
   // float x=(dot(polarHit,newPolar))/2;
//    printf("original point: %f %f %f \n",hit.hitPoint().x,hit.hitPoint().y,hit.hitPoint().z);
//    printf("new point: %f %f %f \n",x,y,1.0f);



    return Point (x,y,0);
}

}