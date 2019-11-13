#ifndef CG1RAYTRACER_GROUPS_BVH_NODE_HEADER
#define CG1RAYTRACER_GROUPS_BVH_NODE_HEADER

#include <rt/bbox.h>
#include <rt/groups/group.h>

namespace rt {

/*
A group is a container of multiple primitives.
*/
class BVHNode {
    public:
        typedef std::vector<Primitive*> Primitives;
        BBox bounds;
        BVHNode *leftChild, *rightChild;
        Primitives nodePrimitives;
        //Point centroid;
        bool isLeaf = true;

        void initLeafNode(BBox &b){
            isLeaf = true;
            leftChild = rightChild = nullptr;
            bounds = b;
            //centroid = bounds.min * .5f + bounds.max * .5f;            
        }

        void initInternalNode(BBox &b){
            isLeaf = false;
            leftChild = new BVHNode();
            rightChild = new BVHNode();
            bounds = b;
            //centroid = bounds.min * .5f + bounds.max * .5f;            
        }       
};
}

#endif