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
    this->h = image.height();
    this->w = image.width();
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
{
    /* TODO */
    this->bh = bh;
    this->ip = i;
    this->img = image;
    this->h = image.height();
    this->w = image.width();
}

RGBColor ImageTexture::getColor(const Point& coord) {
    /* TODO */ 

    float tu, tv, fu, fv, tmpu, tmpv;
    int lu, lv;

    switch(ip){
        case NEAREST:
            tmpu = coord.x * w;
            tmpv = coord.y * h;
            switch (bh)
            {
            case CLAMP:               
                if(tmpu<0.0f) 
                    tu = 0.0f;
                else if(tmpu>w-1)
                    tu = w-1;
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = 0.f;
                else if(tmpv>h-1)
                    tv = h-1;
                else tv = tmpv;
                break;
            case REPEAT:
                if(tmpu<0.0f) 
                    tu = w + fmod(tmpu, w);
                else if(tmpu>w-1)
                    tu = fmod(tmpu, w);
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = h + fmod(tmpv, h);
                else if(tmpv>h-1)
                    tv = fmod(tmpv, h);
                else tv = tmpv;
                break;
            case MIRROR:
                if(tmpu<0.0f) 
                    tu = w + fmod(tmpu, w);
                else if(tmpu>w-1)
                    tu = fmod(tmpu, w);
                    //tu = w - fmod(tmpu, w);
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = h + fmod(tmpv, h);
                else if(tmpv>h-1)
                    //tv = h - fmod(tmpv, h);
                    tv = fmod(tmpv, h);
                else tv = tmpv;
                lu = tmpu / w;
                if(tmpu < 0)
                    lu = lu + 1;
                lv = tmpv / h;
                if(tmpv < 0)
                    lv = lv + 1;
                if(lu%2==1)
                    tu = w - tu;
                if(lv%2==1)
                    tv = h - tv;
                break;
            }
            assert(((int)tu)<=511 && ((int)tv)<=511);
            return img(tu, tv);
            break;
        case BILINEAR:
            tmpu = coord.x * (w-1);
            tmpv = coord.y * (h-1);
            switch (bh)
            {
            case CLAMP:               
                if(tmpu<0.0f) 
                    tu = 0.0f;
                else if(tmpu>w-2)
                    tu = w-2;
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = 0.f;
                else if(tmpv>h-2)
                    tv = h-2;
                else tv = tmpv;
                break;
            case REPEAT:
                if(tmpu<0.0f) 
                    tu = w -1 + fmod(tmpu, w);
                else if(tmpu>w-2)
                    tu = fmod(tmpu, w);
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = h -1 + fmod(tmpv, h);
                else if(tmpv>h-2)
                    tv = fmod(tmpv, h);
                else tv = tmpv;
                break;
            case MIRROR:
                if(tmpu<0.0f) 
                    tu = w-1 + fmod(tmpu, w);
                else if(tmpu>w-1)
                    tu = fmod(tmpu, w)-1;
                else tu = tmpu;

                if(tmpv<0.f) 
                    tv = h-1 + fmod(tmpv, h);
                else if(tmpv>h-1)
                    //tv = h - fmod(tmpv, h);
                    tv = fmod(tmpv, h)-1;
                else tv = tmpv;
                if (!(tu>=0 && (int)tu<=510 && tv>=0 && (int)tv<=510)){
                    //std::cout<<"Issues";
                }
                lu = tmpu / w;
                if(tmpu < 0)
                    lu = lu + 1;
                lv = tmpv / h;
                if(tmpv < 0)
                    lv = lv + 1;
                if(lu%2==1)
                    tu = w-1 - tu;
                if(lv%2==1)
                    tv = h-1 - tv;
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
    /* TODO */
    float tu, fu, tmpu;
    int lu;

    switch(ip) {
        case NEAREST:
            tmpu = coord.x * w;
            switch (bh) {
                case CLAMP:
                    if (tmpu < 0.0f)
                        tu = 0.0f;
                    else if (tmpu > w - 1)
                        tu = w - 1;
                    else tu = tmpu;
                    break;
                case REPEAT:
                    if (tmpu < 0.0f)
                        tu = w + fmod(tmpu, w);
                    else if (tmpu > w - 1)
                        tu = fmod(tmpu, w);
                    else tu = tmpu;
                    break;
                case MIRROR:
                    if (tmpu < 0.0f)
                        tu = w + fmod(tmpu, w);
                    else if (tmpu > w - 1)
                        tu = fmod(tmpu, w);
                        //tu = w - fmod(tmpu, w);
                    else tu = tmpu;

                    lu = tmpu / w;
                    if (tmpu < 0)
                        lu = lu + 1;
                    if (lu % 2 == 1)
                        tu = w - tu;
                    break;
            }
            assert(((int) tu) <= 511);
            return img(tu, h);
        case BILINEAR:
            tmpu = coord.x * (w - 1);
            switch (bh) {
                case CLAMP:
                    if (tmpu < 0.0f)
                        tu = 0.0f;
                    else if (tmpu > w - 2)
                        tu = w - 2;
                    else tu = tmpu;
                    break;
                case REPEAT:
                    if (tmpu < 0.0f)
                        tu = w - 1 + fmod(tmpu, w);
                    else if (tmpu > w - 2)
                        tu = fmod(tmpu, w);
                    else tu = tmpu;
                    break;
                case MIRROR:
                    if (tmpu < 0.0f)
                        tu = w - 1 + fmod(tmpu, w);
                    else if (tmpu > w - 1)
                        tu = fmod(tmpu, w) - 1;
                    else tu = tmpu;

                    lu = tmpu / w;
                    if (tmpu < 0)
                        lu = lu + 1;
                    if (lu % 2 == 1)
                        tu = w - 1 - tu;
                    break;
            }

            if (tu > 510)
                tu = 510;
            if (tu < 0)
                tu = 0;

            fu = tu - (int) tu;
            uint u = floor(tu);
            return lerp(img(u, h), img(u+1, h), fu);
    }
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    /* TODO */
    float tv, fv, tmpv;
    int lv;

    switch(ip){
        case NEAREST:
            tmpv = coord.y * h;
            switch (bh)
            {
                case CLAMP:
                    if(tmpv<0.f)
                        tv = 0.f;
                    else if(tmpv>h-1)
                        tv = h-1;
                    else tv = tmpv;
                    break;
                case REPEAT:
                    if(tmpv<0.f)
                        tv = h + fmod(tmpv, h);
                    else if(tmpv>h-1)
                        tv = fmod(tmpv, h);
                    else tv = tmpv;
                    break;
                case MIRROR:
                    if(tmpv<0.f)
                        tv = h + fmod(tmpv, h);
                    else if(tmpv>h-1)
                        tv = fmod(tmpv, h);
                    else tv = tmpv;

                    lv = tmpv / h;
                    if(tmpv < 0)
                        lv = lv + 1;
                    if(lv%2==1)
                        tv = h - tv;
                    break;
            }
            assert(((int)tv)<=511);
            return img(w, tv);
        case BILINEAR:
            tmpv = coord.y * (h-1);
            switch (bh)
            {
                case CLAMP:
                    if(tmpv<0.f)
                        tv = 0.f;
                    else if(tmpv>h-2)
                        tv = h-2;
                    else tv = tmpv;
                    break;
                case REPEAT:
                    if(tmpv<0.f)
                        tv = h -1 + fmod(tmpv, h);
                    else if(tmpv>h-2)
                        tv = fmod(tmpv, h);
                    else tv = tmpv;
                    break;
                case MIRROR:
                    if(tmpv<0.f)
                        tv = h-1 + fmod(tmpv, h);
                    else if(tmpv>h-1)
                        tv = fmod(tmpv, h)-1;
                    else tv = tmpv;

                    lv = tmpv / h;
                    if(tmpv < 0)
                        lv = lv + 1;
                    if(lv%2==1)
                        tv = h-1 - tv;
                    break;
            }

            if(tv>510)
                tv=510;
            if(tv<0)
                tv=0;

            fv = tv - (int)tv;
            uint v = floor(tv);
            return lerp(img(w, v), img(w, v+1), fv);
    }
}
}