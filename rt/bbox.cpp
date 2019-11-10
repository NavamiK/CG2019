#include <rt/bbox.h>

namespace rt {

BBox BBox::empty() {
    /* TODO */ 
    return BBox();
}

BBox BBox::full() {
    /* TODO */ NOT_IMPLEMENTED;
}


void BBox::extend(const Point& point) {
    /* TODO */    
    if(this->isEmpty){
        min = point;
        max = point;
        this->isEmpty = false;
    }
    else{
        min.x = std::min(point.x, min.x);
        min.y = std::min(point.y, min.y);    
        min.z = std::min(point.z, min.z);

        max.x = std::max(point.x, max.x);
        max.y = std::max(point.y, max.y);
        max.z = std::max(point.z, max.z);
    }
}

void BBox::extend(const BBox& bbox) {
    /* TODO */ 
    if(this->isEmpty){
        min = bbox.min;
        max = bbox.max;
        this->isEmpty = false;
    }
    else{
        min.x = std::min(bbox.min.x, min.x);
        min.y = std::min(bbox.min.y, min.y);    
        min.z = std::min(bbox.min.z, min.z);

        max.x = std::max(bbox.max.x, max.x);
        max.y = std::max(bbox.max.y, max.y);
        max.z = std::max(bbox.max.z, max.z);
    }
}

std::pair<float, float> BBox::intersect(const Ray& ray) const {
    /* TODO */
}

bool BBox::isUnbound() {
    /* TODO */ NOT_IMPLEMENTED;
}

}
