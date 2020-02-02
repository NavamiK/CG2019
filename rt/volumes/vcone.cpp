#include <rt/volumes/vcone.h>
#include <math.h>
namespace rt {

VCone::VCone(float radius, float height, float density, RGBColor color)
{
    /* TODO */
    this->radius = radius;
    this->height = height;
    this->k = radius / height;
    this->density = density;
    this->color = color;
    k = k * k;
}

std::tuple<bool, float, float>  VCone::intersect(const Ray& ray) const {
    /* TODO */ 
    float distance;
    
    float a = ray.d.x * ray.d.x + ray.d.z * ray.d.z - k * ray.d.y * ray.d.y;
    float b = 2 * (ray.d.x * ray.o.x + ray.d.z * ray.o.z - k * ray.d.y * (ray.o.y - height));
    float c = ray.o.x * ray.o.x + ray.o.z * ray.o.z - k * (ray.o.y - height) * (ray.o.y - height);

    float discriminant = (b * b) - (4 * a * c);
    
    if (discriminant <= 0.0f)
        return std::make_tuple(false, 0, 0);
    else {
        float d0 = ( -b + sqrt(discriminant)) / (2 * a);
        float d1 = ( -b - sqrt(discriminant)) / (2 * a);  
        //assert(d0>0)<< "Ray should not originate inside volumetric cone";
        //assert(d1>0)<< "Ray should not originate behind volumetric cone";     
        //if (d0 < 0 || d1 < 0)
          //    return std::make_tuple(false, 0, 0); //no ray marching required
        if(d1 < d0)
            std::swap(d0, d1);

        float yHit = ray.o.y + d1 * ray.d.y;
        if (yHit < 0 || yHit > height)
           return std::make_tuple(false, 0, 0); //Nead only single cone, instead of double        
        
        return std::make_tuple(true, d0, d1);
    }
        
   
}


}
