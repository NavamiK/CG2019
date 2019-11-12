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
    for(uint i = 0; i < primitives.size(); i++){
        primitiveInfos.push_back({primitives[i]->getBounds()});
    }

    std::vector<Primitive*> orderedPrimitives;
    tree = recursiveBuild(primitiveInfos, 0, primitives.size());
}

BVH::BVHNode* BVH::recursiveBuild(std::vector <BVHPrimitiveInfo> primitiveInfoList, int start, int end){
    //recursiveBuild(). build your tree using the split method.
    BVHNode *node = new BVHNode();
    //1. compute bounds of all primitives.
    BBox maxBound;
    for(int i = start; i < end; i++){
        maxBound.extend(primitiveInfoList[i].bounds);
    }

    int nPrimitives = end - start;
    if(nPrimitives == 1){
        node->initLeafNode(maxBound);
        return node;
    }
    else{
        int dim = maxBound.maxExtent();

        float pMid = (maxBound.max.at(dim) + maxBound.min.at(dim)) / 2;
        int mid = (start + end) / 2;

        // need 2 bounding boxes.
        //1. min to pMid
        //2. pMid to max.

        //<Partition primitives into two sets and build children>
        BVHNode *left = recursiveBuild(primitiveInfoList, start, mid);
        BVHNode *right = recursiveBuild(primitiveInfoList, mid, end);
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