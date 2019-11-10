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
        return Intersection::failure(); 
    if (tyNear > txNear) 
        tmaxNear = tyNear; 
    if (tyFar < tminFar) 
        tminFar = tyFar;

    if ((tmaxNear > tzFar) || (tzNear > tminFar)) 
        return  Intersection::failure(); 
    if (tzNear > tmaxNear) 
        tmaxNear = tzNear; 
    if (tzFar < tminFar) 
        tminFar = tzFar; 
  

    /*
    float tmaxNear = max(txNear, tyNear);
    tmaxNear = max(tmaxNear, tzNear);

    float tminFar = min(txFar, tyFar);
    tminFar = min(tminFar, tzFar);
    */
    
    if((tmaxNear > 0) && (tmaxNear < previousBestDistance)){
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
