#include <rt/coordmappers/tmapper.h>

namespace rt {

TriangleMapper::TriangleMapper(Point ntv[3])
{
    /* TODO */
    this->tv0 = ntv[0];
    this->tv1 = ntv[1];
    this->tv2 = ntv[2];
}

TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2)
{
    /* TODO */
    this->tv0 = tv0;
    this->tv1 = tv1;
    this->tv2 = tv2;
}

Point TriangleMapper::getCoords(const Intersection& hit) const {
    /* TODO */ 
    Point local = hit.local();
    //t.x = (tv0.x - tv2.x) * local.x + (tv1.x - tv2.x) * local.y + tv2.x;
    //t.y = (tv0.y - tv2.y) * local.x + (tv1.y - tv2.y) * local.y + tv2.y;
    //t.z = 0.f;
    Point t = local.x * tv0 + local.y * tv1 + local.z * tv2;
    //Point t = local.z * tv0 + local.x * tv1 + local.y * tv2;
    return t;
}

}