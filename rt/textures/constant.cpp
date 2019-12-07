#include <rt/textures/constant.h>

namespace rt {

ConstantTexture::ConstantTexture()
{
    color = RGBColor::rep(0);
}

ConstantTexture::ConstantTexture(const RGBColor& color)
{
    this->color = color;
}

RGBColor ConstantTexture::getColor(const Point& coord) {
    /* TODO */
    return color;
}

RGBColor ConstantTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor ConstantTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

}