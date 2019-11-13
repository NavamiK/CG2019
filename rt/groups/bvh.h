#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>

namespace rt {

class BVH : public Group {
public:
    BVH();
	virtual ~BVH();

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual void rebuildIndex();
    virtual void add(Primitive* p);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);

    // building the tree structure.
    struct BVHNode{
        void initLeafNode(BBox &b){
            leftChild = rightChild = nullptr;
            bounds = b;
            centroid = bounds.min * .5f + bounds.max * .5f;

            isLeaf = true;
        }

        void initInternalNode(BVHNode *left, BVHNode *right){
            leftChild = left;
            rightChild = right;
            bounds.extend(left->bounds);
            bounds.extend(right->bounds);
            centroid = bounds.min * .5f + bounds.max * .5f;

            isLeaf = false;
        }

        BBox bounds;
        BVHNode *leftChild, *rightChild;
        Primitives nodePrimitives;
        Point centroid;

        bool isLeaf;
    };

    BVHNode* recursiveBuild(int start, int end);

    BVHNode* tree;

};

}

#endif