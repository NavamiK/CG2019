
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
    int p1MaxCount = 5;

    float p2MaxHeight = 3.0f;
    float p2MinHeight = 1.0f;
    float p2MaxRotate = 2 * pi;
    float p2MinRotate = 0.f;
    int p2MaxCount = 20;

    float q1MaxHeight = 1.0f;
    float q1MinHeight = 0.2f;
    float q1MaxRotate = 2 * pi;
    float q1MinRotate = 0.f;
    int q1MaxCount = 10;
    
    VGroup* vscene = new VSimpleGroup();
    
    //VCone *normalCone = new VCone(0.03f, 6.0f);
    
    //VInstance* normalInstance = new VInstance(normalCone);
    //vscene->add(normalInstance);
    
    
    for (int i = 0; i < p1MaxCount; ++i) {
        float p1Height = lerp(p1MinHeight, p1MaxHeight, rt::random());
        float p1Angle = lerp(p1MinRotate, p1MaxRotate, rt::random()); 
        
        VCone *p1Cone = new VCone(0.03f, p1Height);
        VInstance* p1Instance = new VInstance(p1Cone);

        p1Instance->rotate(Vector(0, 0, 1.0f), p1Angle);
        p1Instance->translate(Vector(p1Height * sin(p1Angle), -1 * p1Height * cos(p1Angle), 0.0f));
        vscene->add(p1Instance);

        for (int j = 0; j < q1MaxCount; ++j) {
            
            float q1Height = lerp(q1MinHeight, q1MaxHeight, rt::random());
            float q1Angle = lerp(q1MinRotate, q1MaxRotate, rt::random()); 

            VCone *q1Cone = new VCone(0.02f, q1Height);
            VInstance* q1Instance = new VInstance(q1Cone);
            /* //Old code
            q1Instance->rotate(Vector(0, 0, 1.0f), p1Angle);
            q1Instance->translate(Vector(1 * p1Height * sin(p1Angle), -1 * p1Height * cos(p1Angle), 0.0f));
            //q1Instance->rotate(Vector(1 * p1Height * sin(p1Angle), -1 * p1Height * cos(p1Angle), 1.0), q1Angle);
            */
            q1Instance->rotate(Vector(0, 0, 1.0f), q1Angle);
            q1Instance->translate(Vector(1 * p1Height * sin(p1Angle), -1 * p1Height * cos(p1Angle), 0.0f));
            vscene->add(q1Instance);
        }
    }
    
    
    for (int i = 0; i < p2MaxCount; ++i) {
        float height = lerp(p2MinHeight, p2MaxHeight, rt::random());
        float angle = lerp(p2MinRotate, p2MaxRotate, rt::random()); 
        
        VCone *cone = new VCone(0.03f, height);
        VInstance* instance = new VInstance(cone);
        //if(rt::random() < 0.5)
            //instance->rotate(Vector(rt::random(), rt::random(), rt::random()), angle);
        //else
            instance->rotate(Vector(-10 * rt::random(), -10 * rt::random(), -10 * rt::random()), angle);
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
    renderFireworks(0.001f, "a9-1.png", 30);
}