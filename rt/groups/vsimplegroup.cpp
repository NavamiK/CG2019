#include <rt/groups/vsimplegroup.h>

namespace rt {
/*
BBox SimpleGroup::getBounds() const {
    BBox groupBbox = BBox::empty();
    BBox primitiveBbox;
    for (auto iter = primitives.begin(); iter != primitives.end(); ++iter){
        primitiveBbox = (*iter)->getBounds();
        groupBbox.extend(primitiveBbox);
    } 
    return groupBbox; 
}
*/
/*
std::tuple<bool, float, float> SimpleGroup::intersect(const Ray& ray) const {
    Intersection nearestIntersection = Intersection::failure();
    Intersection currentIntersection;
    for (auto iter = vCones.begin(); iter != vCones.end(); ++iter){
        currentIntersection = (*iter)->intersect(ray);
        if(currentIntersection){
            nearestIntersection = currentIntersection;
            previousBestDistance = nearestIntersection.distance;
        }
    }
    return nearestIntersection;
}
*/

void VSimpleGroup::rebuildIndex() {
    //do nothing
}

void VSimpleGroup::add(VInstance* p) {
    /* TODO */ 
    vInstances.push_back(p);
}


}
