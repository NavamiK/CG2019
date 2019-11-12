#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>
#include <cmath>

namespace rt {

class Ray;
static const float NEG_INF = -INFINITY;
static const float POS_INF = INFINITY;

class BBox {
public:
    Point min, max;

    BBox() {}

    BBox(bool isEmpty, bool isFull){
        this->isEmpty = isEmpty;
        this->isFull = isFull;
        if(isFull){
            min.x = NEG_INF;
            min.y = NEG_INF;
            min.z = NEG_INF;
            max.x = POS_INF;
            max.y = POS_INF;
            max.z = POS_INF;
        }
    }

    BBox(const Point& min, const Point& max)
    {
        this->isEmpty = false;
        this->isFull = false;
        this->min = min;
        this->max = max;
    }

    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    Vector diagonal() const {
        return max - min;
    }

    std::pair<float, float> intersect(const Ray& ray) const;

    int maxExtent() const;//decide which axis is the largest.
    Point axisPoint(int axis, float dimScalar) const;

    bool isUnbound();
private:
    bool isEmpty, isFull;
};

}

#endif