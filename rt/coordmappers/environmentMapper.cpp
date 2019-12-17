#include <rt/coordmappers/environmentMapper.h>

namespace rt{
  EnvironmentMapper::EnvironmentMapper(const rt::Point &origin, const rt::Vector &longitudinalAxis,const rt::Vector &polarAxis) {
      this->origin = origin;
      this->longitudinalAxis = longitudinalAxis;
      this->polarAxis = polarAxis;
  }

  Point EnvironmentMapper::getCoords(const rt::Intersection &hit) const {
      Vector lA = longitudinalAxis;
      Vector pA = polarAxis;
      Vector newPolar = (pA.normalize()- dot(lA.normalize(),pA.normalize())*lA).normalize();
      Vector dir = hit.ray.d;
      float y= dot(lA.normalize(),dir)/lA.length();  // works better than v

      Vector polarHit=(dir - dot(lA.normalize(),dir)*lA.normalize()).normalize();
      float x=(dot(polarHit,newPolar)) * pA.length();

      return Point (x,y,0);
  }
};