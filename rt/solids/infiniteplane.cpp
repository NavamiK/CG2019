#include <rt/solids/infiniteplane.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material)
{
    this->origin = origin;
	this->normal = normal;
    this->material = material;
    if(texMapper!=nullptr) this->texMapper = texMapper;
    /* TODO */
}

BBox InfinitePlane::getBounds() const {
    /* TODO */ 
    return BBox::full();
}

Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */   
    float denom = dot(ray.d,normal);
    
    if(denom < EPSILON && denom> -EPSILON)
        return Intersection::failure();

    float distance = dot(origin - ray.o, normal)/denom;
    if((distance >=0) && (distance < previousBestDistance)){
        float normalSign = -1;
        if(denom < 0)
            normalSign = 1;
		Point p = ray.o + distance * ray.d;
		Intersection intersection(distance, ray, this, normal, ray.getPoint(distance));
		return intersection;
    }
	else
		return Intersection::failure();
}

Solid::Sample InfinitePlane::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float InfinitePlane::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
