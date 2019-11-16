#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

#include <core/vector.h>


#include <core/point.h>


#include <rt/groups/group.h>
#include <rt/bbox.h>
#include "bvhnode.h"

namespace rt {

class BVH : public Group {
public:
    BVH();
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual void rebuildIndex();
	virtual ~BVH();
    void add(Primitive* p);
    void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
    void buildTree(BVHNode * root);

private:
    BVHNode *root = new BVHNode();
    bool isSAH=false;

};

}

#endif