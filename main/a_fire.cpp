
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
    
    //scene->add(new Sphere(Point(150.0f, 100.0f, 240.0f)*scale, 99.0f*scale, nullptr, nullptr));
    //scene->add(new Sphere(Point(450.0f, 50.0f, 50.0f)*scale, 49.0f*scale, nullptr, nullptr));
    //VSphere testSphere(Point(150.0f, 100.0f, 240.0f)*scale, 150.0f*scale);
    VCone testCone(Point(150.0f, 100.0f, 240.0f)*scale, 0.3f*scale, 20.0f*scale);

    RayTraceFireIntegrator integrator(&world, testCone);
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