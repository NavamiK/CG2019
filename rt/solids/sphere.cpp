#include <rt/solids/sphere.h>
#include <math.h>
namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
{
    this->center = center;
    this->radius = radius;
    /* TODO */
}

BBox Sphere::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
    Vector sphereCenter(center.x, center.y, center.z);
    Vector rayOrigin(ray.o.x, ray.o.y, ray.o.z);
    float distance = (dot(ray.d, sphereCenter)-dot(ray.d, rayOrigin))/dot(ray.d, ray.d);
    if(((rayOrigin + distance*ray.d - sphereCenter).lensqr() <= radius) && (distance < previousBestDistance)){
        Point p = ray.o + distance * ray.d;
        Vector normal = rayOrigin + distance*ray.d - sphereCenter;
        Intersection i(distance,ray,this,normal,p);
        return i;
    }
    else
        return Intersection::failure();

}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    return M_PI*radius*radius;
}

}
