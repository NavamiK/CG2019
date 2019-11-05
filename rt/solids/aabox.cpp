#include <rt/solids/aabox.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
{
    /* TODO */
    this->corner1 = corner1;
    this->corner2 = corner2;
}

BBox AABox::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ 
    float distance;
    float txNear = (corner1.x - ray.o.x) / ray.d.x;
    float txFar = (corner2.x - ray.o.x) / ray.d.x;
    float tyNear = (corner1.y - ray.o.y) / ray.d.y;
    float tyFar = (corner2.y - ray.o.y) / ray.d.y;
    float tzNear = (corner1.z - ray.o.z) / ray.d.z;
    float tzFar = (corner2.z - ray.o.z) / ray.d.z;
    
    float tmaxNear = max(txNear, tyNear);
    tmaxNear = max(tmaxNear, tzNear);

    float tminFar = min(txFar, tyFar);
    tminFar = min(tminFar, tzFar);
    
    if((tmaxNear < tminFar) && (tmaxNear < previousBestDistance)){
        distance = tmaxNear;
        Vector normal;
        Point p = ray.o + distance * ray.d;
        Intersection intersection(distance, ray, this, normal, p);
        return intersection;
    }
	else
		return Intersection::failure();
}

}
