#include <rt/coordmappers/environmentMapper.h>

namespace rt{
  EnvironmentMapper::EnvironmentMapper(const rt::Point &origin, const rt::Vector &longitudinalAxis,const rt::Vector &polarAxis) {

  }

  Point EnvironmentMapper::getCoords(const rt::Intersection &hit) const {
    Vector v = hit.ray.d;
    return (Point(v.x, v.y, v.z)); // maybe this should be changed.
  }
};