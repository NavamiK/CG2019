#include <rt/bbox.h>
#include <rt/solids/aabox.h>

namespace rt {

BBox BBox::empty() {
    /* TODO */ 
    bool isEmpty = true;
    bool isFull = false;
    return BBox(isEmpty, isFull);
}

BBox BBox::full() {
    /* TODO */ 
    bool isEmpty = false;
    bool isFull = true;
    return BBox(isEmpty, isFull);
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
    if(isFull)
        return std::make_pair(NEG_INF, POS_INF);
    else if(isEmpty)
        return std::make_pair(POS_INF, NEG_INF);
    else{
        AABox aabox(min, max, nullptr, nullptr);
        auto[isIntersect, entry, exit, normal] = aabox.findRayEntryExit(ray);
        if(isIntersect)
            return std::make_pair(entry, exit);
        else
            return std::make_pair(POS_INF, NEG_INF); //Return failure (t2>t1) case
    }

}

bool BBox::isUnbound() {
    /* TODO */ 
    if((min.x == NEG_INF && max.x == POS_INF)
        ||(min.y == NEG_INF && max.y == POS_INF)
        ||(min.z == NEG_INF && max.z == POS_INF))
        return true;
    else return false;
}

int BBox::maxExtent() const {
    Vector d = diagonal();
    if(d.x > d.y && d.x > d.z)
        return 0;
    else if(d.y > d.z)
        return 1;
    else
        return 2;
}

Point BBox::axisPoint(int axis, float dimScalar) const{
    if(axis == 0){//x axis
        return (Point(max.x*dimScalar, max.y, max.z));
    }
    else if(axis == 1){// y axis
        return (Point(max.x, max.y*dimScalar, max.z));
    }

    return (Point(max.x, max.y, max.z * dimScalar));// the z axis.
}

Point BBox::getCentroid(){
    Point centroid; 
    centroid.x = (min.x + max.x)/2;
    centroid.y = (min.y + max.y)/2;
    centroid.z = (min.z + max.z)/2;
    return centroid;
}
}
