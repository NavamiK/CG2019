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
        primitiveInfos.push_back({i, primitives[i]->getBounds()});
    }

    std::vector<Primitive*> orderedPrimitives;
    tree = recursiveBuild(primitiveInfos, 0, primitives.size(), orderedPrimitives);
}

    BVH::BVHNode* BVH::recursiveBuild(std::vector <BVHPrimitiveInfo> primitiveInfoList, int start, int end, std::vector<Primitive*> orderedPrims){
        //recursiveBuild(). build your tree using the split method.
        BVHNode *node = new BVHNode();
        //1. compute bounds of all primitives.
        BBox maxBound;
        for(int i = 0; i < primitiveInfoList.size(); i++){
            maxBound.extend(primitiveInfoList[i].bounds);
        }

        int nPrimitives = end - start;

        if(nPrimitives == 1){
            // create leave nodes.
            int firstPrimOffset = orderedPrims.size();
           // int fistPrimOffset = primitives.size();
            for(uint i = 0; i < primitives.size(); i++){
                int num = primitiveInfoList[i].primitiveNumber;
                orderedPrims.push_back(primitives[num]);
            }
            node->initLeafNode(firstPrimOffset, nPrimitives, maxBound);
            return node;
        }
        else{
            BBox centroidBounds;
            for(int i = 0; i < primitives.size(); i++){
                centroidBounds.extend(primitiveInfoList[i].centriod);
            }
            int dim = centroidBounds.maxExtent();


            float pMid = (centroidBounds.max.at(dim) + centroidBounds.min.at(dim)) / 2;
            int mid = (start + end) / 2;
            if(centroidBounds.max.at(dim) == centroidBounds.min.at(dim)){
                // create leave nodes.
                int fistPrimOffset = primitives.size();
                for(uint i = 0; i < primitives.size(); i++){
                    int num = primitiveInfoList[i].primitiveNumber;
                    orderedPrims.push_back(primitives[num]);
                }
                node->initLeafNode(fistPrimOffset, nPrimitives, maxBound);
                return node;
            }
            else{
                //partition primitives based on split method.
                BVHPrimitiveInfo *midPtr = std::partition(&primitiveInfoList[start], &primitiveInfoList[end-1]+1,
                                                          [dim, pMid](const BVHPrimitiveInfo &pi){
                                                              return pi.centriod.at(dim) < pMid;
                                                          });

                mid = midPtr - &primitiveInfoList[0];

                //<Partition primitives into two sets and build children>
                BVHNode *left = recursiveBuild(primitiveInfoList, start, mid, orderedPrims);
                BVHNode *right = recursiveBuild(primitiveInfoList, mid, end, orderedPrims);
                node->initInternalNode(dim, left, right);
            }
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