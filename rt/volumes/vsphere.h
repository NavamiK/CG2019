#ifndef CG1RAYTRACER_VOLUMES_SPHERE_HEADER
#define CG1RAYTRACER_VOLUMES_SPHERE_HEADER

#include <tuple>
#include <core/point.h>
#include <core/vector.h>
#include <rt/ray.h>

namespace rt {

class VSphere {
public:
    VSphere() {}
    VSphere(const Point& center, float radius);

    std::tuple<bool, float, float> intersect(const Ray& ray) const;
    
    //virtual Sample sample() const;
    //virtual float getArea() const;
private:
    Point center;
    float radius;
};

}


#endif