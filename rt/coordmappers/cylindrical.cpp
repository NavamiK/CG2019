#include <rt/coordmappers/cylindrical.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
{
    /* TODO need to clean up*/ 
    this->origin = origin;
    this->lA = longitudinalAxis;
    this->pA = polarAxis;
    this->scaleY = longitudinalAxis.length();
    this->scaleX = polarAxis.length();
}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    /* TODO */     
    Vector hitP=hit.local()-origin;
    //Projection of hitP onto lA gives y-component, divide by lA.length as this is height of cylinder
    float v = dot(lA.normalize(),hitP)/lA.length();  

    //Remove the component of pA along lA, to make pA orthogonal to lA
    Vector perpPolar = (pA - dot(lA.normalize(),pA)*lA);
   
    //Project hitP onto the plane perpendicular to lA, & containing origin
    Vector polarHit = (hitP - v * lA).normalize();

    //phi in the plane between new polar axis and projector vector
    float u = acos(dot(polarHit, perpPolar));
    return Point(u,v,0);
}

}