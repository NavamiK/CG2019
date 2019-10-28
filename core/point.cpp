#include <core/point.h>
#include <core/float4.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <core/vector.h>

namespace rt {

Point::Point(float x, float y, float z)
{
    /* TODO */
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(const Float4& f4)
{
    /* TODO */ NOT_IMPLEMENTED;
}

Vector Point::operator - (const Point& b) const {
    /* TODO */ 
    float scalar = -1.0;
    Point res  = scalar * (*this);
    return Vector(res.x, res.y, res.z);
}

bool Point::operator == (const Point& b) const {
    /* TODO */ 
    if(x == b.x && y == b.y && z == b.z)
        return true;
    else 
        return false;
}

bool Point::operator != (const Point& b) const {
    /* TODO */ 
    bool isequal = (*this) == b; 
    return !isequal;
}

Point operator * (float scalar, const Point& b) {
    /* TODO */
    Point res;
    res.x = scalar * b.x;
    res.y = scalar * b.y;
    res.z = scalar * b.z;
    return res;
}

Point operator * (const Point& a, float scalar) {
    /* TODO */
    Point res;
    res = scalar * a;
    return res;
}

Point min(const Point& a, const Point& b) {
    /* TODO */ 
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
    /* TODO */ 
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
