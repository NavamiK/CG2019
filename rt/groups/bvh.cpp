#include <rt/groups/bvh.h>

namespace rt {

BVH::BVH()
{
    /* TODO */
}

BVH::~BVH() {
    /* TODO */
}

void BVH::rebuildIndex() {
    tree = recursiveBuild(0, primitives.size());
}

BVH::BVHNode* BVH::recursiveBuild(int start, int end){
    BVHNode *node = new BVHNode();
    //1. compute bounds of all primitives.
    BBox maxBound;
    Primitives nodePrimitives;
    for(int i = start; i < end; i++){
        maxBound.extend(primitives[i]->getBounds());
        nodePrimitives.push_back(primitives[i]);
    }

    if(nodePrimitives.size() < 3){
        // create leave node and stop.
        node->initLeafNode(maxBound);
        return node;
    }
    else{
        int splitAxis = maxBound.maxExtent();
        float dimScalar = (maxBound.max.at(splitAxis) + maxBound.min.at(splitAxis)) / 2.f;
        Point splitAxisPoint = maxBound.axisPoint(splitAxis, dimScalar);
        int mid = (start + end) / 2;
        // build child nodes and increase the node bounds to include the point.
        BVHNode *left = recursiveBuild(start, mid);
        left->bounds.extend(splitAxisPoint);
        BVHNode *right = recursiveBuild(mid, end);
        right->bounds.extend(splitAxisPoint);

        node->initInternalNode(left, right);
    }
}

BBox BVH::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::add(Primitive* p) {
    primitives.push_back(p);
}

void BVH::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

}