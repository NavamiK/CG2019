#include <rt/solids/sphere.h>
#include <math.h>
namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
{
    /* TODO */
    this->center = center;
    this->radius = radius;
}

BBox Sphere::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ 
    float distance;
    Vector oc = ray.o - center;
    float a = dot(ray.d, ray.d);
    float b = 2.0 * dot(oc, ray.d);
    float c = dot(oc, oc) - radius * radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant > 0.0f)
        distance = min(-b + sqrt(discriminant) / (2 * a), -b  - sqrt(discriminant) / (2 * a));
    else if(discriminant == 0.0f )
       distance = -b / (2*a);
    else
        return Intersection::failure();

    if(distance < previousBestDistance){
        Point p = ray.o + distance * ray.d;
        Vector normal = p - center;
        Intersection intersection(distance, ray, this, normal, p);
        return intersection;
    }
    else
        return Intersection::failure();
}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    /* TODO */ 
    return M_PI*radius*radius;
}

}
