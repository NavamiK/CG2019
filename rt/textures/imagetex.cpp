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
    tu = coord.x;
    tv = coord.y;
    //assert(tu>=0 && tv>=0);
    switch(ip){
        case NEAREST:
            tmpu = tu * (img.width());
            tmpv = tv * (img.height());
            switch (bh)
            {
            case CLAMP:               
                if(tmpu<0) 
                    tu = 0;
                else if(tmpu>1)
                    tu = 1;
                else tu = tmpu;

                if(tmpv<0) 
                    tv = 0;
                else if(tmpv>1)
                    tv = 1;
                else tv = tmpv;
                break;
            case REPEAT:
                tu = tmpu - (int)tmpu;
                tv = tmpv - (int)tmpv;
                break;
            case MIRROR:
                tu = tmpu - (int)tmpu;
                tv = tmpv - (int)tmpv;
                lu = (int)tmpu;
                lv = (int)tmpv;
                if(lu %2==1)
                   tu = 1 - tu;
                if(lv %2==1)
                   tv = 1 - tv;
                break;
            }
            u = tu * (img.width());
            v = tv * (img.height());    
            lu = min((int)u, (int)img.width()-1);
            lv = min((int)v, (int)img.height()-1);
             //if(lu>511 ||lv>511 )
               // std::cout<<" lu no ";
            //return img(1,1);
            return img(lu, lv);
            break;
        case BILINEAR:
            tmpu = tu * (img.width()-1);
            tmpv = tv * (img.height()-1);
            switch (bh){
            case CLAMP:               
                if(tmpu<0) 
                    tu = 0;
                else if(tmpu>1)
                    tu = 1;
                else tu = tmpu;

                if(tmpv<0) 
                    tv = 0;
                else if(tmpv>1)
                    tv = 1;
                else tv = tmpv;
                break;
            case REPEAT:
                tu = tmpu - (int)tmpu;
                tv = tmpv - (int)tmpv;
                break;
            case MIRROR:
                tu = tmpu - (int)tmpu;
                tv = tmpv - (int)tmpv;
                lu = (int)tmpu;
                lv = (int)tmpv;
                if(lu %2==1)
                   tu = 1 - tu;
                if(lv %2==1)
                   tv = 1 - tv;
                break;
            }
            u = tu * (img.width()-1);
            v = tv * (img.height()-1);
            lu = min((int)u, (int)img.width()-2);
            lv = min((int)v, (int)img.height()-2);
            /*
            fu = u - (int)u;
            fv = v - (int)v;
            if(u>510 ||v>510 )
                std::cout<<"no u: " <<u << " v: "<<v;
            return img(1,1);
            //return lerp2d(img(u,v), img(u,(int)v+1), img((int)u+1, v), img((int)u+1, (int)v+1), fv, fu);
            */
            fu = u - lu;
            fv = v - lv;
            //if(lu>510 ||lv>510 )
               // std::cout<<"no u: " <<u << " v: "<<v;
            //return img(1,1);
            return lerp2d(img(lu,lv), img(lu,lv+1), img(lu+1, v), img(lu+1, lv+1), fv, fu);
    
    }
    
}

RGBColor ImageTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}
}