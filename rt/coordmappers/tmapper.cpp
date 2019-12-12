#include <rt/coordmappers/tmapper.h>

namespace rt {

TriangleMapper::TriangleMapper(Point ntv[3])
{
    /* TODO */
    this->tv0 = ntv[0];
    this->tv1 = ntv[1];
    this->tv2 = ntv[2];
    this->area = getArea();
}

TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2)
{
    /* TODO */
    this->tv0 = tv0;
    this->tv1 = tv1;
    this->tv2 = tv2;
    this->area = getArea();
}

Point TriangleMapper::getCoords(const Intersection& hit) const {
    /* TODO */ 
    Point bary;
    Point p = hit.local();
    bary.x = getArea(tv1 - p, tv2 - p) / area;
    bary.y = getArea(tv0 - p, tv2 - p) / area;
    bary.z = getArea(tv0 - p, tv1 - p) / area;
    assert(bary.x >=0  && bary.y >=0 && bary.z >=0);
    return bary;
}

float TriangleMapper::getArea() const {
    /* TODO */ 
    Vector edge1 = tv1 - tv0;
    Vector edge2 = tv2 - tv0;
    return getArea(edge1, edge2);
}

float TriangleMapper::getArea(const Vector& edge1, const Vector& edge2) const{
    return cross(edge1, edge2).length()/2;
}

}