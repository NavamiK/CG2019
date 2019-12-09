#include <rt/textures/imagetex.h>

namespace rt {

ImageTexture::ImageTexture()
{
    /* TODO */
    this->bh = REPEAT;
    this->ip = BILINEAR;
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i)
{
    /* TODO */
    this->bh = bh;
    this->ip = i;
    Image image(512,512);
    image.readPNG(filename);
    this->img = image;
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
{
    /* TODO */
    this->bh = bh;
    this->ip = i;
    this->img = image;
}

RGBColor ImageTexture::getColor(const Point& coord) {
    /* TODO */ 
    NOT_IMPLEMENTED;
}

RGBColor ImageTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}
}