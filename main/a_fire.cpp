
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/solids/sphere.h>

#include <rt/cameras/perspective.h>
#include <rt/solids/quad.h>
#include <rt/groups/simplegroup.h>
#include <rt/materials/dummy.h>
#include <rt/materials/lambertian.h>
#include <rt/textures/constant.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>
#include <rt/lights/projectivelight.h>

#include <rt/integrators/raytracefire.h>
#include <rt/cameras/dofperspective.h>
#include <rt/volumes/vcone.h>
#include <rt/primmod/vinstance.h>
#include <rt/groups/vsimplegroup.h>

using namespace rt;

namespace {

void renderFireworks(float scale, const char* filename, int numSamples=1) {

    Image img(400, 400);
    World world;
    Group* scene = new SimpleGroup();
    world.scene = scene;

    //PerspectiveCamera cam(Point(278*scale, 273*scale, -800*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);
    PerspectiveCamera cam(Point(0, 0, 10), Vector(0, 0, -1), Vector(0, 1, 0), pi/3, pi/3);
    //DOFPerspectiveCamera dofcam(Point(278*scale, 273*scale, -800*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f, 1.025f, 0.045f);
    
    VGroup* vscene = new VSimpleGroup();
    VCone *instanceCone = new VCone(30.0f*scale, 4000.0f*scale);
    //VCone *instanceCone = new VCone(0.3f*scale, 20.0f*scale);
    //VCone *instanceCone = new VCone(30.0f*scale, -4000.0f*scale);
    
    VInstance* normal = new VInstance(instanceCone);
    //vscene->add(normal);
    
    //VCone *instanceCone2 = new VCone(30.0f*scale, -4000.0f*scale);
    VInstance* second = new VInstance(instanceCone);
    //second->scale(Vector(1.0f, 1.0f + 0.3f, 1.0f));
    second->translate(Vector(0.0f, -4000.0f*scale, 0.0f));
    //second->rotate(Vector(0.0f, 0.0f, 1.0f),pi);
    vscene->add(second);
    
    RayTraceFireIntegrator integrator(&world, vscene);
    Renderer engine(&cam, &integrator);
     if (numSamples>1)
        engine.setSamples(numSamples);
    engine.render(img);
    img.writePNG(filename);

}
}


void a_fire() {
    renderFireworks(0.001f, "a9-1.png", 20);
}