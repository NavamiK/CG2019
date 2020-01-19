#include <rt/volumes/vsphere.h>
#include <math.h>
namespace rt {

VSphere::VSphere(const Point& center, float radius)
{
    /* TODO */
    this->center = center;
    this->radius = radius;
}

std::tuple<bool, float, float>  VSphere::intersect(const Ray& ray) const {
    /* TODO */ 
    float distance;
    Vector oc = ray.o - center;
    float a = dot(ray.d, ray.d);
    float b = 2.0f * dot(oc, ray.d);
    float c = dot(oc, oc) - (radius * radius);

    float discriminant = (b * b) - (4 * a * c);
    if (discriminant >= 0.0f){
        float d0 = ( -b + sqrt(discriminant)) / (2 * a);
        float d1 = ( -b - sqrt(discriminant)) / (2 * a);         
        if(d1 < d0)
            std::swap(d0, d1);
        assert(d0>0)<< "Ray should not originate inside volumetric sphere";
        assert(d1>0)<< "Ray should not originate inside volumetric sphere";
        return std::make_tuple(true, d0, d1);
    } 
    else 
        return std::make_tuple(false, 0, 0);
   
}


}
