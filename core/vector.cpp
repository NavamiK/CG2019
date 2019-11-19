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
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(const Float4& f4)
{
    /* TODO */
    this->x = f4.x - f4.w;
    this->y = f4.y - f4.w;
    this->z = f4.z - f4.w;    
}

Vector Vector::operator + (const Vector& b) const {
    Vector sum;
    sum.x = x + b.x;
    sum.y = y + b.y;
    sum.z = z + b.z;
    return sum;
}

Vector Vector::operator - (const Vector& b) const {
    Vector diff;
    diff.x = x - b.x;
    diff.y = y - b.y;
    diff.z = z - b.z;
    return diff;
}

Vector Vector::operator - () const {
    float scalar = -1.0;
    Vector res  = scalar * (*this);
    return res;
}

Vector Vector::normalize() const {
    float len = length();
    Vector res  = (*this) / len;
    return res;
}

Vector operator * (float scalar, const Vector& b) {
    Vector res;
    res.x = scalar * b.x;
    res.y = scalar * b.y;
    res.z = scalar * b.z;
    return res;
}

Vector operator * (const Vector& a, float scalar) {
    Vector res;
    res = scalar * a;
    return res;
}

Vector operator / (const Vector& a, float scalar) {
    scalar = 1.0 / scalar;
    Vector res;
    res = scalar * a;
    return res;
}

Vector cross(const Vector& a, const Vector& b) {
    Vector res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return res;
}

float dot(const Vector& a, const Vector& b) {
    float res; 
    res = a.x * b.x + a.y * b.y + a.z * b.z;
    return res;
}

float Vector::lensqr() const {
    float res = dot(*this, *this);
    return res;
}

float Vector::length() const {
    float len = sqrt(lensqr());
    return len;
}

bool Vector::operator == (const Vector& b) const {
    if(x == b.x && y == b.y && z == b.z)
        return true;
    else 
        return false;
}

bool Vector::operator != (const Vector& b) const {
    bool isequal = (*this) == b; 
    return !isequal;
}

Vector min(const Vector& a, const Vector& b) {
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
    Point sum;
    sum.x = a.x + b.x;
    sum.y = a.y + b.y;
    sum.z = a.z + b.z;
    return sum;
}

Point operator + (const Vector& a, const Point& b) {
    Point sum;
    sum.x = a.x + b.x;
    sum.y = a.y + b.y;
    sum.z = a.z + b.z;
    return sum;
}

Point operator - (const Point& a, const Vector& b) {
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
