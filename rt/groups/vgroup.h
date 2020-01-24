#ifndef CG1RAYTRACER_GROUPS_VGROUP_HEADER
#define CG1RAYTRACER_GROUPS_VGROUP_HEADER

#include <vector>
#include <rt/primmod/vinstance.h>

namespace rt {

/*
A group is a container of multiple primitives.
*/
class VGroup {
public:
    typedef std::vector<VInstance*> VInstances;
    virtual void rebuildIndex() = 0;
    virtual void add(VInstance* p) = 0;
    VInstances vInstances;
};

}

#endif