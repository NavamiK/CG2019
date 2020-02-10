#ifndef CG1RAYTRACER_PRIMMOD_VINSTANCE_HEADER
#define CG1RAYTRACER_PRIMMOD_VINSTANCE_HEADER

#include <core/vector.h>
#include <rt/volumes/vcone.h>
#include <core/matrix.h>
#include <core/scalar.h>

namespace rt {

class VInstance {
public:
    VInstance(VCone * content);
    VCone* content();

    void reset(); //reset transformation back to identity
    void translate(const Vector& t);
    void rotate(const Vector& axis, float angle);
    void scale(float scale);
    void scale(const Vector& scale);

    //BBox getBounds() const;
    std::tuple<bool, float, float> intersect(const Ray& ray) const;

private:
    VCone *archetype;
    Matrix transformation;// should check if this is correct.
    Matrix invTrans;
    //We store the bounding box for the instance, which is updated with each transformation on the primitive
    //BBox instanceBounds;

    //void computeBounds();
};

}

#endif