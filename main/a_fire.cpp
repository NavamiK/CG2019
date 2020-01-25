
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
#include <core/interpolate.h>
#include <core/random.h>

using namespace rt;

namespace {

VGroup* makeTestSparkleFlames(){

    VGroup* vscene = new VSimpleGroup();
    
    VCone *instanceCone = new VCone(0.03f, 2.0f);
    
    VInstance* normal = new VInstance(instanceCone);
    vscene->add(normal);
    
    VInstance* second = new VInstance(instanceCone);
    //second->scale(Vector(1.0f, 1.0f + 0.3f, 1.0f));
    second->translate(Vector(0.0f, -6.0f, 0.0f));
    //second->rotate(Vector(0.0f, 0.0f, 1.0f),pi);
    vscene->add(second);

    return vscene;
}

VGroup* makeSparkleFlames(){
    float p1MaxHeight = 5.0f;
    float p1MinHeight = 1.0f;
    float p1MaxRotate = 2 * pi;
    float p1MinRotate = 0.f;
    int p1MaxCount = 3;

    float p2MaxHeight = 3.0f;
    float p2MinHeight = 1.0f;
    float p2MaxRotate = 2 * pi;
    float p2MinRotate = 0.f;
    int p2MaxCount = 20;
    
    VGroup* vscene = new VSimpleGroup();
    
    VCone *normalCone = new VCone(0.03f, 6.0f);
    
    VInstance* normalInstance = new VInstance(normalCone);
    //vscene->add(normalInstance);
    
    
    for (int i = 0; i < p1MaxCount; ++i) {
        float height = lerp(p1MinHeight, p1MaxHeight, rt::random());
        float angle = lerp(p1MinRotate, p1MaxRotate, rt::random()); 
        
        VCone *cone = new VCone(0.03f, height);
        VInstance* instance = new VInstance(cone);

        instance->rotate(Vector(0, 0, 1.0f), angle);
        instance->translate(Vector(height * sin(angle), -1 * height * cos(angle), 0.0f));

        VCone *qcone = new VCone(0.03f, height);
        VInstance* qinstance = new VInstance(qcone);
        qinstance->rotate(Vector(0, 0, 1.0f), angle);
        qinstance->translate(Vector(2 * height * sin(angle), -2 * height * cos(angle), 0.0f));
        qinstance->rotate(Vector(0, 0, 1.0), angle);

        vscene->add(instance);
        //vscene->add(qinstance);
    }
    
    for (int i = 0; i < p2MaxCount; ++i) {
        float height = lerp(p2MinHeight, p2MaxHeight, rt::random());
        float angle = lerp(p2MinRotate, p2MaxRotate, rt::random()); 
        
        VCone *cone = new VCone(0.03f, height);
        VInstance* instance = new VInstance(cone);
        //if(rt::random() < 0.5)
            //instance->rotate(Vector(rt::random(), rt::random(), rt::random()), angle);
        //else
            instance->rotate(Vector(-1 * rt::random(), -1 * rt::random(), -1 * rt::random()), angle);
        vscene->add(instance);
    }
    

    return vscene;
}

void renderFireworks(float scale, const char* filename, int numSamples=1) {

    Image img(400, 400);
    //Image img(1920, 1080);
    World world;
    Group* scene = new SimpleGroup();
    world.scene = scene;

    //PerspectiveCamera cam(Point(278*scale, 273*scale, -800*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);
    PerspectiveCamera cam(Point(0, 0, 10), Vector(0, 0, -1), Vector(0, 1, 0), pi/3, pi/3);
    //DOFPerspectiveCamera dofcam(Point(0, 0, 10), Vector(0, 0, -1), Vector(0, 1, 0), pi/3, pi/3, 1.025f, 0.045f);
    
    VGroup *vscene = makeSparkleFlames();
    RayTraceFireIntegrator integrator(&world, vscene);

    Renderer engine(&cam, &integrator);
     if (numSamples>1)
        engine.setSamples(numSamples);
    engine.render(img);
    img.writePNG(filename);

}
}


void a_fire() {
    renderFireworks(0.001f, "a9-1.png", 3);
}