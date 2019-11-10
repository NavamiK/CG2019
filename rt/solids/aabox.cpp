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
    //int signx, signy, signz;
    float txNear, txFar, tyNear, tyFar, tzNear, tzFar;
    if (ray.d.x >= 0){
        txNear = (corner1.x - ray.o.x) / ray.d.x;
        txFar = (corner2.x - ray.o.x) / ray.d.x;
    }
    else{
        txFar = (corner1.x - ray.o.x) / ray.d.x;
        txNear = (corner2.x - ray.o.x) / ray.d.x;
    }
    if (ray.d.y >= 0){
        tyNear = (corner1.y - ray.o.y) / ray.d.y;
        tyFar = (corner2.y - ray.o.y) / ray.d.y;
    }
    else{
        tyFar = (corner1.y - ray.o.y) / ray.d.y;
        tyNear = (corner2.y - ray.o.y) / ray.d.y;
    }
    if (ray.d.z >= 0){
        tzNear = (corner1.z - ray.o.z) / ray.d.z;
        tzFar = (corner2.z - ray.o.z) / ray.d.z;
    }else{
        tzFar = (corner1.z - ray.o.z) / ray.d.z;
        tzNear = (corner2.z - ray.o.z) / ray.d.z;
    }
    
    float tmaxNear = max(txNear, tyNear);
    tmaxNear = max(tmaxNear, tzNear);

    float tminFar = min(txFar, tyFar);
    tminFar = min(tminFar, tzFar);
    
    if((tmaxNear > 0) && (tmaxNear <= tminFar) && (tmaxNear < previousBestDistance)){
        distance = tmaxNear;
        Vector normal;
        if(tmaxNear == txNear){
            if (txNear< txFar)
                normal = Vector(-1.0f, 0, 0);
            else 
                normal = Vector(1.0f, 0, 0);
        }
        else if(tmaxNear == tyNear){
            if (tyNear< tyFar)
                normal = Vector(0, -1.0f, 0);
            else 
                normal = Vector(0, 1.0f, 0);
        }            
        else{
            if (tzNear< tzFar)
                normal = Vector(0, 0, 1.0f);
            else 
                normal = Vector(0, 0, -1.0f);
        }        
        Intersection intersection(distance, ray, this, normal, ray.getPoint(distance));
        return intersection;
    }
	else
		return Intersection::failure();
}

}
