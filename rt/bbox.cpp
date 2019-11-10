#include <rt/bbox.h>

namespace rt {

BBox BBox::empty() {
    /* TODO */ NOT_IMPLEMENTED;
}

BBox BBox::full() {
    /* TODO */ NOT_IMPLEMENTED;
}


void BBox::extend(const Point& point) {
    /* TODO */    
    
    min.x = std::min(point.x, min.x);
    min.y = std::min(point.y, min.y);    
    min.z = std::min(point.z, min.z);

    max.x = std::max(point.x, max.x);
    max.y = std::max(point.y, max.y);
    max.z = std::max(point.z, max.z);
}

void BBox::extend(const BBox& bbox) {
    /* TODO */ 

}

std::pair<float, float> BBox::intersect(const Ray& ray) const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool BBox::isUnbound() {
    /* TODO */ NOT_IMPLEMENTED;
}

}
