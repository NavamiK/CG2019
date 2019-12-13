#include <rt/textures/imagetex.h>
#include <core/interpolate.h>
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
    Image image;
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
    /* Implemented as per lecture notes, doesn't work for given image */
    float tu, tv, fu, fv, u, v, tmpu, tmpv;
    int lu, lv;
    //tu = coord.x;
    //tv = coord.y;
    //assert(tu>=0 && tv>=0);
    switch(ip){
        case NEAREST:
            tmpu = coord.x * (img.width());
            tmpv = coord.y * (img.height());
            switch (bh)
            {
            case CLAMP:               
                if(tmpu<0.0f) 
                    tu = 0.0f;
                else if(tmpu>img.width()-1)
                    tu = img.width()-1;
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = 0.f;
                else if(tmpv>img.height()-1)
                    tv = img.height()-1;
                else tv = tmpv;
                break;
            case REPEAT:
                if(tmpu<0.0f) 
                    tu = img.width() + fmod(tmpu, img.width());
                else if(tmpu>img.width()-1)
                    tu = fmod(tmpu, img.width());
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = img.height() + fmod(tmpv, img.height());
                else if(tmpv>img.height()-1)
                    tv = fmod(tmpv, img.height());
                else tv = tmpv;
                break;
            case MIRROR:
                if(tmpu<0.0f) 
                    tu = img.width() + fmod(tmpu, img.width());
                else if(tmpu>img.width()-1)
                    tu = fmod(tmpu, img.width());
                    //tu = img.width() - fmod(tmpu, img.width());
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = img.height() + fmod(tmpv, img.height());
                else if(tmpv>img.height()-1)
                    //tv = img.height() - fmod(tmpv, img.height());
                    tv = fmod(tmpv, img.height());
                else tv = tmpv;
                lu = tmpu / img.width();
                if(tmpu < 0)
                    lu = lu + 1;
                lv = tmpv / img.height();
                if(tmpv < 0)
                    lv = lv + 1;
                if(lu%2==1)
                    tu = img.width() - tu;
                if(lv%2==1)
                    tv = img.height() - tv;
                break;
            }
            assert(((int)tu)<=511 && ((int)tv)<=511);
            return img(tu, tv);
            break;
        case BILINEAR:
            tmpu = coord.x * (img.width()-1);
            tmpv = coord.y * (img.height()-1);
            switch (bh)
            {
            case CLAMP:               
                if(tmpu<0.0f) 
                    tu = 0.0f;
                else if(tmpu>img.width()-2)
                    tu = img.width()-2;
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = 0.f;
                else if(tmpv>img.height()-2)
                    tv = img.height()-2;
                else tv = tmpv;
                break;
            case REPEAT:
                if(tmpu<0.0f) 
                    tu = img.width() -1 + fmod(tmpu, img.width());
                else if(tmpu>img.width()-2)
                    tu = fmod(tmpu, img.width());
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = img.height() -1 + fmod(tmpv, img.height());
                else if(tmpv>img.height()-2)
                    tv = fmod(tmpv, img.height());
                else tv = tmpv;
                break;
            case MIRROR:
                if(tmpu<0.0f) 
                    tu = img.width()-1 + fmod(tmpu, img.width());
                else if(tmpu>img.width()-1)
                    tu = fmod(tmpu, img.width())-1;
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = img.height()-1 + fmod(tmpv, img.height());
                else if(tmpv>img.height()-1)
                    //tv = img.height() - fmod(tmpv, img.height());
                    tv = fmod(tmpv, img.height())-1;
                else tv = tmpv;
                if (!(tu>=0 && (int)tu<=510 && tv>=0 && (int)tv<=510)){
                    //std::cout<<"Issues";
                }
                lu = tmpu / img.width();
                if(tmpu < 0)
                    lu = lu + 1;
                lv = tmpv / img.height();
                if(tmpv < 0)
                    lv = lv + 1;
                if(lu%2==1)
                    tu = img.width()-1 - tu;
                if(lv%2==1)
                    tv = img.height()-1 - tv;
                //assert(((int)tu)<=510 && ((int)tv)<=510);
                break;
            }
                 
            if(tu>510)
                tu = 510;
            if(tv>510)
                tv=510;
            if(tu<0)
                tu=0;
            if(tv<0)
                tv=0;
            fu = tu - (int)tu;
            fv = tv - (int)tv;
            //assert(((int)tu)<=509 && ((int)tv)<=509);
            uint u = floor(tu);
            uint v = floor(tv);
            return lerp2d(img(u,v), img(u,v+1), img(u+1, v), img(u+1, v+1), fv, fu);
            //if(v==389)
            //std::cout<<"Wait";
            //return img(u,v);
    
    }
    
}

RGBColor ImageTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}
}