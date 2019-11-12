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
        }

        void initInternalNode(int d, BVHNode *left, BVHNode *right){
            leftChild = left;
            rightChild = right;
            dim = d;
            //This may change.
            bounds.extend(left->bounds);
            bounds.extend(right->bounds);
        }

        BBox bounds;
        BVHNode *leftChild, *rightChild;
        int dim;
    };

    struct BVHPrimitiveInfo{
        BVHPrimitiveInfo() = default;
        BVHPrimitiveInfo(uint num, const BBox &b):
                primitiveNumber(num), bounds(b),
                centriod(b.min * .5f + b.max * .5f) {}

        uint primitiveNumber;
        BBox bounds;
        Point centriod;
    };

    BVHNode* recursiveBuild(std::vector <BVHPrimitiveInfo> primitiveInfoList, int start, int end,
                            std::vector<Primitive*> orderedPrims);

    BVHNode *tree;

};

}

#endif