#include <core/float4.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/assert.h>
#include <core/scalar.h>

namespace rt {

Float4::Float4(float x, float y, float z, float w) {
    /* TODO */
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Float4::Float4(const Point& p) {
    /* TODO */
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
    this->w = 1;
}

Float4::Float4(const Vector& vec) {
    /* TODO */ 
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
    this->w = 0;
}

float& Float4::operator [] (int idx) {
    /* TODO */ 
    NOT_IMPLEMENTED;
}

float Float4::operator [] (int idx) const {
    /* TODO */ 
    float val;
    switch (idx){
        case 0:
            val = this->x;
            break;
        case 1:
            val = this->y;
            break;
        case 2:
            val = this->z;
            break;
        case 3:
            val = this->w;
            break;
    }
    return val;
}

Float4 Float4::operator + (const Float4& b) const {
    /* TODO */ 
    Float4 res;
    res.x = this->x + b.x;
    res.y = this->y + b.y; 
    res.z = this->z + b.z;
    res.w = this->w + b.w; 
    return res;
}

Float4 Float4::operator - (const Float4& b) const {
    /* TODO */ 
    Float4 res;
    res.x = this->x - b.x;
    res.y = this->y - b.y; 
    res.z = this->z - b.z;
    res.w = this->w - b.w; 
    return res;
}

Float4 Float4::operator * (const Float4& b) const {
    /* TODO */ 
    Float4 res;
    res.x = this->x * b.x;
    res.y = this->y * b.y; 
    res.z = this->z * b.z;
    res.w = this->w * b.w; 
    return res;
}

Float4 Float4::operator / (const Float4& b) const {
    /* TODO */
    Float4 res;
    res.x = this->x / b.x;
    res.y = this->y / b.y; 
    res.z = this->z / b.z;
    res.w = this->w / b.w; 
    return res;
}

Float4 operator * (float scalar, const Float4& b) {
    /* TODO */ 
    Float4 res;
    res.x = scalar * b.x;
    res.y = scalar * b.y; 
    res.z = scalar * b.z;
    res.w = scalar * b.w; 
    return res;
}

Float4 operator * (const Float4& a, float scalar) {
    /* TODO */ 
    Float4 res;
    res.x = scalar * a.x;
    res.y = scalar * a.y; 
    res.z = scalar * a.z;
    res.w = scalar * a.w; 
    return res;
}

Float4 operator / (const Float4& a, float scalar) {
    /* TODO */ 
    Float4 res;
    res.x = a.x / scalar;
    res.y = a.y / scalar; 
    res.z = a.z / scalar;
    res.w = a.w / scalar; 
    return res;
}

float dot(const Float4& a, const Float4& b) {
    /* TODO */
    float res = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    return res;
}

Float4 Float4::operator - () const {
    /* TODO */ 
    Float4 res;
    return res * (-1.0f);    
}

bool Float4::operator == (const Float4& b) const {
    /* TODO */ 
    if(x == b.x && y == b.y && z == b.z && w == b.z)
        return true;
    else 
        return false;
}

bool Float4::operator != (const Float4& b) const {
    /* TODO */ 
    bool isequal = (*this) == b; 
    return !isequal;
}

Float4 min(const Float4& a, const Float4& b) {
    /* TODO */
    Float4 res;
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
    if(a.w < b.w)
        res.w = a.w;
    else
        res.w = b.w;
    return res;
}

Float4 max(const Float4& a, const Float4& b) {
    /* TODO */ 
    Float4 res;
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
    if(a.w > b.w)
        res.w = a.w;
    else
        res.w = b.w;
    return res;
}

}