#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <core/random.h>
#include <rt/cameras/camera.h>
#include <rt/integrators/integrator.h>

namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1)
{}

void Renderer::render(Image& img) {
    /* TODO */ 
    int resy = img.height();
    int resx = img.width();
    int prcx, prcy;
    float ndcx, ndcy, sscx, sscy;
    Ray ray;
    for(prcx = 0; prcx < resx; prcx++)
        for(prcy = 0; prcy < resy; prcy++){
            if(samples == 1){
                ndcx = (prcx + 0.5f) / resx;
                ndcy = (prcy + 0.5f) / resy;
                // Screen space coordinates [-1, 1]
                sscx = ndcx * 2.0f - 1;
                sscy = -(ndcy * 2.0f - 1);
                ray = (this->cam)->getPrimaryRay(sscx, sscy);
                RGBColor pixelColor = (this->integrator)->getRadiance(ray);
                img(prcx, prcy) = pixelColor;
            }
            else{
                RGBColor pixcelColorSum = RGBColor::rep(0.f);
                ndcx = (prcx) / resx;//Don't shot through the pixel center.
                ndcy = (prcy) / resy;
                // Screen space coordinates [-1, 1]
                sscx = ndcx * 2.0f - 1;
                sscy = -(ndcy * 2.0f - 1);

                for(int s = 0; s < samples; s++){
                    ray = (this->cam)->getPrimaryRay(sscx * random(), sscy * random());
                    pixcelColorSum = pixcelColorSum + (this->integrator)->getRadiance(ray);
                }
                img(prcx, prcy) = pixcelColorSum / samples;
            }

        }
}

}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt {

void Renderer::test_render1(Image& img) {
    int resy = img.height();
    int resx = img.width();
    int prcx, prcy;
    for(prcx = 0; prcx < resx; prcx++)
        for(prcy = 0; prcy < resy; prcy++){
            img(prcx, prcy) = a1computeColor(prcx, prcy, resx, resy); 
        }
}
}

rt::RGBColor a2computeColor(const rt::Ray& r);

namespace rt {

void Renderer::test_render2(Image& img) {
    int resy = img.height();
    int resx = img.width();
    int prcx, prcy;
    float ndcx, ndcy, sscx, sscy;
    Ray ray;
    for(prcx = 0; prcx < resx; prcx++)
        for(prcy = 0; prcy < resy; prcy++){
            ndcx = (prcx + 0.5f) / resx;
            ndcy = (prcy + 0.5f) / resy;
            // Screen space coordinates [-1, 1]
            sscx = ndcx * 2.0f - 1;
            sscy = ndcy * 2.0f - 1;           
            ray = (this->cam)->getPrimaryRay(sscx, sscy);
            img(prcx, prcy) = a2computeColor(ray); 
        }
}
}
