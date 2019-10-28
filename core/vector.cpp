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
    /*
    Vector neg;
    int scale = -1;
    neg.x =  - b.x;
    diff.y =  - b.y;
    diff.z =  - b.z;
    */
    float scalar = -1.0;
    Vector res  = scalar * (*this);
    return res;
}

Vector Vector::normalize() const {
    /* TODO */ 
    NOT_IMPLEMENTED;
    /*
    float len = this.length();
    Vector res  = (*this) / scalar;
    return res;
    */
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
    /* TODO */ NOT_IMPLEMENTED;
}

float dot(const Vector& a, const Vector& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

float Vector::lensqr() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Vector::length() const {
    /* TODO */ NOT_IMPLEMENTED;
}


bool Vector::operator == (const Vector& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool Vector::operator != (const Vector& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector min(const Vector& a, const Vector& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector max(const Vector& a, const Vector& b) {
    /* TODO */NOT_IMPLEMENTED;
}

Point operator + (const Point& a, const Vector& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Point operator + (const Vector& a, const Point& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Point operator - (const Point& a, const Vector& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Point operator * (const Float4& scale, const Point& p) {
    /* TODO */NOT_IMPLEMENTED;
}

/* Additional utility members*/
void Vector::print(){
    std::cout << x << "," << y <<"," << z <<std::endl;
}

}
