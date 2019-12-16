#include <rt/coordmappers/world.h>

namespace rt {

Point WorldMapper::getCoords(const Intersection& hit) const {
    /* TODO */ 
    Point worldHitCoord = hit.local();    
    Point worldHitCoordScaled;
    worldHitCoordScaled.x = worldHitCoord.x * scale.x;
    worldHitCoordScaled.y = worldHitCoord.y * scale.y;
    worldHitCoordScaled.z = worldHitCoord.z * scale.z;
    return worldHitCoordScaled;
}

WorldMapper::WorldMapper()
{
    /* TODO */
    this->scale = Float4::rep(1.0f);
}

WorldMapper::WorldMapper(const Float4& scale)
{
    /* TODO */
    this->scale = scale;
}

}