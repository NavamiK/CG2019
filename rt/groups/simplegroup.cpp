#include <rt/groups/simplegroup.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    /* TODO */ 
    BBox groupBbox = BBox::empty();
    BBox primitiveBbox;
    for (auto iter = primitives.begin(); iter != primitives.end(); ++iter){
        primitiveBbox = (*iter)->getBounds();
        groupBbox.extend(primitiveBbox);
    } 
    return groupBbox; 
}

Intersection SimpleGroup::intersect( const Ray& ray, float previousBestDistance) const {
    /* TODO */ 
    Intersection nearestIntersection = Intersection::failure();
    Intersection currentIntersection;
    for (auto iter = primitives.begin(); iter != primitives.end(); ++iter){
        currentIntersection = (*iter)->intersect(ray, previousBestDistance);
        if(currentIntersection){
            nearestIntersection = currentIntersection;
            previousBestDistance = nearestIntersection.distance;
        }
    }
    return nearestIntersection;
}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
    /* TODO */ 
    primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    /* TODO */ 
    for (auto iter = primitives.begin(); iter != primitives.end(); ++iter){
        (*iter)->setMaterial(m);
    } 
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
