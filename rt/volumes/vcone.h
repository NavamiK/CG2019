#ifndef CG1RAYTRACER_VOLUMES_CONE_HEADER
#define CG1RAYTRACER_VOLUMES_CONE_HEADER

#include <tuple>
#include <core/point.h>
#include <core/vector.h>
#include <rt/ray.h>

namespace rt {

class VCone {
public:
    VCone() {}
    VCone(float radius, float height, float density);

    std::tuple<bool, float, float> intersect(const Ray& ray) const;
    float density;
    
    //virtual Sample sample() const;
    //virtual float getArea() const;
private:
    float radius;
    float height;
    float k;
};

}


#endif