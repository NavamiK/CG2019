#include <core/color.h>
#include <core/scalar.h>
#include <core/float4.h>

namespace rt {

RGBColor::RGBColor(const Float4& f4)
{
/* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::operator + (const RGBColor& c) const {
    RGBColor sum;
    sum.r = r + c.r;
    sum.g = g + c.g;
    sum.b = b + c.b;
    return sum;
}

RGBColor RGBColor::operator - (const RGBColor& c) const {
    RGBColor res;
    res.r = r - c.r;
    res.g = g - c.g;
    res.b = b - c.b;
    return res;
}

RGBColor RGBColor::operator * (const RGBColor& c) const {
    RGBColor res;
    res.r = r * c.r;
    res.g = g * c.g;
    res.b = b * c.b;
    return res;
}

bool RGBColor::operator == (const RGBColor& c) const {
    if(r == c.r && g == c.g && b == c.b)
        return true;
    else 
        return false;
}

bool RGBColor::operator != (const RGBColor& b) const {
    bool isequal = (*this) == b; 
    return !isequal;
}

RGBColor RGBColor::clamp() const {
    RGBColor res(r,g,b);
    float min = 0.0f;
    float max = 1.0f;
    if(r < min)
        res.r = min;
    else if(r > max)
        res.r = max;
    if(g < min)
        res.g = min;
    else if(g > max)
        res.g = max;
    if(b < min)
        res.b = min;
    else if(b > max)
        res.b = max;
    return res;
}

RGBColor RGBColor::gamma(float gam) const {
    /* TODO */ NOT_IMPLEMENTED;
}

float RGBColor::luminance() const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor operator * (float scalar, const RGBColor& c) {
    RGBColor res;
    res.r = scalar * c.r;
    res.g = scalar * c.g;
    res.b = scalar * c.b;
    return res;
}

RGBColor operator * (const RGBColor& c, float scalar) {
    RGBColor res;
    res = scalar * c;
    return res;
}

RGBColor operator / (const RGBColor& c, float scalar) {
    scalar = 1.0 / scalar;
    RGBColor res;
    res = scalar * c;
    return res;
}

}