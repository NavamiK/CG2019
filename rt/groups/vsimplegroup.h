#ifndef CG1RAYTRACER_GROUPS_VSIMPLEGROUP_HEADER
#define CG1RAYTRACER_GROUPS_VSIMPLEGROUP_HEADER

#include <rt/groups/vgroup.h>

namespace rt {

class VSimpleGroup : public VGroup {
public:
    //virtual BBox getBounds() const;
    //virtual std::tuple<bool, float, float> intersect(const Ray& ray) const;
    virtual void rebuildIndex();
    virtual void add(VInstance* p);
};

}

#endif