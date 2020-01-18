#include <rt/volumes/vcone.h>
#include <math.h>
namespace rt {

VCone::VCone(const Point& center, float radius, float height)
{
    /* TODO */
    this->center = center;
    this->radius = radius;
    this->height = height;
    this->k = radius / height;
    k = k * k;
}

std::tuple<bool, float, float>  VCone::intersect(const Ray& ray) const {
    /* TODO */ 
    float distance;
    /*
    float a = ray.d.x * ray.d.x + ray.d.y * ray.d.y - k * ray.d.z * ray.d.z;
    float b = 2 * (ray.d.x * ray.o.x + ray.d.y * ray.o.y - k * ray.d.z * (ray.o.z - height));
    float c = ray.o.x * ray.o.x + ray.o.y * ray.o.y - k * (ray.o.z - height) * (ray.o.z - height);
    */

    float a = ray.d.x * ray.d.x + ray.d.z * ray.d.z - k * ray.d.y * ray.d.y;
    float b = 2 * (ray.d.x * ray.o.x + ray.d.z * ray.o.z - k * ray.d.y * (ray.o.y - height));
    float c = ray.o.x * ray.o.x + ray.o.z * ray.o.z - k * (ray.o.y - height) * (ray.o.y - height);

    float discriminant = (b * b) - (4 * a * c);
    if (discriminant >= 0.0f){
        float d0 = ( -b + sqrt(discriminant)) / (2 * a);
        float d1 = ( -b - sqrt(discriminant)) / (2 * a);  

        assert(d0>0)<< "Ray should not originate inside volumetric cone";
        assert(d1>0)<< "Ray should not originate behind volumetric cone";       
        if(d1 < d0)
            std::swap(d0, d1);
        
        return std::make_tuple(true, d0, d1);
    } 
    else 
        return std::make_tuple(false, 0, 0);
   
}


}
