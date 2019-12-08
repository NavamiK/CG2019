#include <rt/textures/checkerboard.h>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black)
{
    /* TODO */
    this->white = white;
    this->black = black;
}

RGBColor CheckerboardTexture::getColor(const Point& coord) {
    /* TODO */
    /* Multiply by 2 to reduce edge length from 1 to 0.5 */
    int lu = coord.x * 2;
    int lv = coord.y * 2;
    int lw = coord.z * 2;
    int parity = (lu + lv + lw) % 2;
    if(parity == 0)
        return black;
    else 
        return white;
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

}