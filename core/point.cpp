#include <core/point.h>
#include <core/float4.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <core/vector.h>

namespace rt {

Point::Point(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(const Float4& f4)
{
    /* TODO */ NOT_IMPLEMENTED;
}

Vector Point::operator - (const Point& b) const {
    Vector res;
    res.x = x - b.x;
    res.y = y - b.y;
    res.z = z - b.z;
    return res;
}

bool Point::operator == (const Point& b) const {
    if(x == b.x && y == b.y && z == b.z)
        return true;
    else 
        return false;
}

bool Point::operator != (const Point& b) const {
    bool isequal = (*this) == b; 
    return !isequal;
}

Point operator * (float scalar, const Point& b) {
    Point res;
    res.x = scalar * b.x;
    res.y = scalar * b.y;
    res.z = scalar * b.z;
    return res;
}

Point operator * (const Point& a, float scalar) {
    Point res;
    res = scalar * a;
    return res;
}

Point min(const Point& a, const Point& b) {
    Point res;
    if(a.x < b.x)
        res.x = a.x;
    else
        res.x = b.x;
    if(a.y < b.y)
        res.y = a.y;
    else
        res.y = b.y;
    if(a.z < b.z)
        res.z = a.z;
    else
        res.z = b.z;
    return res;
}

Point max(const Point& a, const Point& b) {
    Point res;
    if(a.x > b.x)
        res.x = a.x;
    else
        res.x = b.x;
    if(a.y > b.y)
        res.y = a.y;
    else
        res.y = b.y;
    if(a.z > b.z)
        res.z = a.z;
    else
        res.z = b.z;
    return res;
}

}
