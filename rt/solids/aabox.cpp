#include <rt/solids/aabox.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
{
    /* TODO */
    this->corner1 = corner1;
    this->corner2 = corner2;
}

BBox AABox::getBounds() const {
    /* TODO */ 
    return BBox(corner1, corner2);
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    /* TODO */ 
    float xlen = abs(corner2.x - corner1.x);
    float ylen = abs(corner2.y - corner1.y);
    float zlen = abs(corner2.z - corner1.z);
    return 2 * (xlen * ylen + ylen * zlen + zlen * xlen);
}

std::tuple<bool, float, float, Vector> AABox::findRayEntryExit(const Ray& ray) const{
    /* TODO */ 
    float distance;
    float txNear, txFar, tyNear, tyFar, tzNear, tzFar;
    Vector rayDirInv = Vector(1/ray.d.x,1/ray.d.y,1/ray.d.z); 

    if (rayDirInv.x >= 0){
        txNear = (corner1.x - ray.o.x) * rayDirInv.x;
        txFar = (corner2.x - ray.o.x) * rayDirInv.x;
    }
    else{
        txFar = (corner1.x - ray.o.x) * rayDirInv.x;
        txNear = (corner2.x - ray.o.x) * rayDirInv.x;
    }
    if (rayDirInv.y >= 0){
        tyNear = (corner1.y - ray.o.y) * rayDirInv.y;
        tyFar = (corner2.y - ray.o.y) * rayDirInv.y;
    }
    else{
        tyFar = (corner1.y - ray.o.y) * rayDirInv.y;
        tyNear = (corner2.y - ray.o.y) * rayDirInv.y;
    }
    if (rayDirInv.z >= 0){
        tzNear = (corner1.z - ray.o.z) * rayDirInv.z;
        tzFar = (corner2.z - ray.o.z) * rayDirInv.z;
    }else{
        tzFar = (corner1.z - ray.o.z) * rayDirInv.z;
        tzNear = (corner2.z - ray.o.z) * rayDirInv.z;
    }

    float tmaxNear = txNear; 
    float tminFar = txFar;

    if ((txNear > tyFar) || (tyNear > txFar)) 
        return std::make_tuple(false, 0.f, 0.f, Vector());
    if (tyNear > txNear) 
        tmaxNear = tyNear; 
    if (tyFar < tminFar) 
        tminFar = tyFar;

    if ((tmaxNear > tzFar) || (tzNear > tminFar)) 
        return std::make_tuple(false, 0.f, 0.f, Vector()); 
    if (tzNear > tmaxNear) 
        tmaxNear = tzNear; 
    if (tzFar < tminFar) 
        tminFar = tzFar; 
  
    //if((tmaxNear > 0)){
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
    return std::make_tuple(true, tmaxNear, tminFar, normal);      
    //return std::make_tuple(false, 0.f, 0.f, Vector()); 
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
    auto[isIntersect, entry, exit, normal] = findRayEntryExit(ray);
    if(isIntersect && (entry>0) && (entry < previousBestDistance)){
        Intersection intersection(entry, ray, this, normal, ray.getPoint(entry));
        return intersection;
    }
	else
		return Intersection::failure();
}

}
