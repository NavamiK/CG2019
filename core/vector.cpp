#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>
#include <core/assert.h>
#include <algorithm>
#include <cmath>

namespace rt {

Vector::Vector(float x, float y, float z)
{
    /* TODO */
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(const Float4& f4)
{
    /* TODO */
}

Vector Vector::operator + (const Vector& b) const {
    /* TODO */ 
    Vector sum;
    sum.x = x + b.x;
    sum.y = y + b.y;
    sum.z = z + b.z;
    return sum;
}

Vector Vector::operator - (const Vector& b) const {
    /* TODO */ 
    Vector diff;
    diff.x = x - b.x;
    diff.y = y - b.y;
    diff.z = z - b.z;
    return diff;
}

Vector Vector::operator - () const {
    /* TODO */ 
    float scalar = -1.0;
    Vector res  = scalar * (*this);
    return res;
}

Vector Vector::normalize() const {
    /* TODO */ 
    float len = length();
    Vector res  = (*this) / len;
    return res;
}

Vector operator * (float scalar, const Vector& b) {
    /* TODO */ 
    Vector res;
    res.x = scalar * b.x;
    res.y = scalar * b.y;
    res.z = scalar * b.z;
    return res;
}

Vector operator * (const Vector& a, float scalar) {
    /* TODO */ 
    Vector res;
    res = scalar * a;
    return res;
}

Vector operator / (const Vector& a, float scalar) {
    /* TODO */
    scalar = 1.0 / scalar;
    Vector res;
    res = scalar * a;
    return res;
}

Vector cross(const Vector& a, const Vector& b) {
    /* TODO */ 
    Vector res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return res;
}

float dot(const Vector& a, const Vector& b) {
    /* TODO */ 
    float res; 
    res = a.x * b.x + a.y * b.y + a.z * b.z;
    return res;
}

float Vector::lensqr() const {
    /* TODO */ 
    float res = dot(*this, *this);
    return res;
}

float Vector::length() const {
    /* TODO */ 
    float len = sqrt(lensqr());
    return len;
}

bool Vector::operator == (const Vector& b) const {
    /* TODO */ 
    if(x == b.x && y == b.y && z == b.z)
        return true;
    else 
        return false;
}

bool Vector::operator != (const Vector& b) const {
    /* TODO */ 
    bool isequal = (*this) == b; 
    return !isequal;
}

Vector min(const Vector& a, const Vector& b) {
    /* TODO */ 
    Vector res;
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

Vector max(const Vector& a, const Vector& b) {
    /* TODO */    
    Vector res;
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

Point operator + (const Point& a, const Vector& b) {
    /* TODO */ 
    Point sum;
    sum.x = a.x + b.x;
    sum.y = a.y + b.y;
    sum.z = a.z + b.z;
    return sum;
}

Point operator + (const Vector& a, const Point& b) {
    /* TODO */ 
    Point sum;
    sum.x = a.x + b.x;
    sum.y = a.y + b.y;
    sum.z = a.z + b.z;
    return sum;
}

Point operator - (const Point& a, const Vector& b) {
    /* TODO */ 
    Point sum;
    sum.x = a.x - b.x;
    sum.y = a.y - b.y;
    sum.z = a.z - b.z;
    return sum;
}

Point operator * (const Float4& scale, const Point& p) {
    /* TODO */NOT_IMPLEMENTED;
}

/* Additional utility members*/
void Vector::print(){
    std::cout << x << "," << y <<"," << z <<std::endl;
}

}
