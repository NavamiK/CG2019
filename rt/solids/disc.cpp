#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
{
    /* TODO */
    this->center = center;
    this->radius = radius;
    this->normal = normal;
}

BBox Disc::getBounds() const {
    /* TODO */ 
    float radX = radius * sqrt( 1.0f - (normal.x * normal.x));
    float radY = radius * sqrt( 1.0f - (normal.y * normal.y));
    float radZ = radius * sqrt( 1.0f - (normal.z * normal.z));
    Vector rad(radX, radY, radZ);
    return BBox(center - rad, center + rad);
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ 
    float distance;
    Vector discOrigin(center.x, center.y, center.z);
    Vector rayOrigin(ray.o.x, ray.o.y, ray.o.z);

    distance = (dot(discOrigin, normal) - dot(rayOrigin,normal))/dot(ray.d,normal);
    Point hitPoint = ray.o + distance * ray.d;
    Vector hitPointCenter = hitPoint - center;
	if ((distance >=0) && (hitPointCenter.length() <= radius) && (distance < previousBestDistance)){
		Intersection intersection(distance, ray, this, normal, hitPoint);
		return intersection;
    }
	else
		return Intersection::failure();
}

Solid::Sample Disc::sample() const {
    NOT_IMPLEMENTED;
}

float Disc::getArea() const {
    /* TODO */ 
    return M_PI * radius * radius;
}

}
