
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
#include <rt/solids/cylinder.h>
#include <rt/primmod/instance.h>
#include <rt/solids/infiniteplane.h>
#include <rt/textures/perlin.h>
#include<random>

using namespace rt;

namespace {
std::default_random_engine g;
std::normal_distribution<> d(pi,1);
/*
VGroup* makeTestSparkleFlames(){

    VGroup* vscene = new VSimpleGroup();
    
    VCone *instanceCone = new VCone(0.03f, 2.0f);
    
    VInstance* normal = new VInstance(instanceCone);
    vscene->add(normal);
    
    VInstance* second = new VInstance(instanceCone);
    second->translate(Vector(0.0f, -6.0f, 0.0f));
    vscene->add(second);

    return vscene;
}
*/

void makeSparkleFlameGroup(VGroup* vscene, Vector groupOrigin, int p1MaxCount, int p2MaxCount, int p3MaxCount, int q1MaxCount){
    float p1MaxHeight = 4.0f;
    float p1MinHeight = 1.0f;
    float p1MaxRotate = pi/2;
    float p1MinRotate = -pi/2;

    float p2MaxHeight = 2.5f;
    float p2MinHeight = 1.0f;
    float p2MaxRotate = 2 * pi;
    float p2MinRotate = 0.f;

    float q1MaxHeight = 1.0f;
    float q1MinHeight = 0.2f;
    float q1MaxRotate = 2 * pi;
    float q1MinRotate = 0.f;
    
    //float stepSize = 0.005f;
    float minStepSize = 0.002f;
    float maxStepSize = 0.08f;
    float stepSize;
    
    for (int i = 0; i < p1MaxCount; ++i) {
        float p1Height = lerp(p1MinHeight, p1MaxHeight, rt::random());
        //float p1Angle = lerp(p1MinRotate, p1MaxRotate, rt::random()); 
        //float p1Angle = rt::random(p1MinRotate, p1MaxRotate);
        float p1Angle = d(g);
        stepSize = random(minStepSize, maxStepSize);

        VCone *p1Cone = new VCone(0.03f, p1Height, stepSize);
        VInstance* p1Instance = new VInstance(p1Cone);

        p1Instance->rotate(Vector(0, 0, 1.0f), p1Angle);
        p1Instance->translate(Vector(p1Height * sin(p1Angle), -1 * p1Height * cos(p1Angle), 0.0f));
        p1Instance->translate(groupOrigin);
        vscene->add(p1Instance);
        //Secondary flames
        for (int j = 0; j < q1MaxCount; ++j) {        
            float q1Height = lerp(q1MinHeight, q1MaxHeight, rt::random());
            float q1Angle = lerp(q1MinRotate, q1MaxRotate, rt::random(-0.5f, 0.5f)); 
            stepSize = random(minStepSize, maxStepSize);

            VCone *q1Cone = new VCone(0.02f, q1Height, stepSize);
            VInstance* q1Instance = new VInstance(q1Cone);
            //q1Instance->translate(Vector(0, 5, 0));
            q1Instance->rotate(Vector(0, 0, 1.0f), q1Angle);
            q1Instance->translate(Vector(1 * p1Height * sin(p1Angle), -1 * p1Height * cos(p1Angle), 0.0f));
            q1Instance->translate(groupOrigin);
            vscene->add(q1Instance);
        }
    }
    
    //Primary flames
    for (int i = 0; i < p2MaxCount; ++i) {
        float height = lerp(p2MinHeight, p2MaxHeight, rt::random());
        float angle = lerp(p2MinRotate, p2MaxRotate, rt::random()); 
        stepSize = random(minStepSize, maxStepSize);
        
        VCone *cone = new VCone(0.03f, height, stepSize);
        VInstance* instance = new VInstance(cone);
        instance->rotate(Vector(0, 0, 1.0f), angle);
        instance->translate(groupOrigin);
        vscene->add(instance);
    } 
    //Primary flames inverted
    for (int i = 0; i < p3MaxCount; ++i) {
        float height = rt::random(p2MinHeight, p2MaxHeight);
        float angle = rt::random(p2MinRotate, p2MaxRotate); 
        stepSize = random(minStepSize, maxStepSize);

        VCone *cone = new VCone(0.03f, height, stepSize);
        VInstance* instance = new VInstance(cone);
        instance->rotate(Vector(0, 0, 1.0f), angle);
        instance->translate(Vector(height * sin(angle), -1 * height * cos(angle), 0.0f));
        instance->translate(groupOrigin);
        vscene->add(instance);
    }    
}

VGroup* makeSparkleFlames(){
    Vector g1Center = Vector(0, 4, -2);
    Vector g2Center = Vector(3, 1.5, 0);
    Vector g3Center = Vector(-2, 2, 0);
    /*HRES*/
    /*
    int g1p1MaxCount = 4, g1q1MaxCount = 10, g1p2MaxCount = 20, g1p3MaxCount = 5;
    int g2p1MaxCount = 3, g2q1MaxCount = 8, g2p2MaxCount = 15, g2p3MaxCount = 4;
    int g3p1MaxCount = 6, g3q1MaxCount = 9, g3p2MaxCount = 18, g3p3MaxCount = 3;
    */
    /*LRES*/
    int g1p1MaxCount = 4, g1q1MaxCount = 5, g1p2MaxCount = 5, g1p3MaxCount = 3;
    int g2p1MaxCount = 3, g2q1MaxCount = 4, g2p2MaxCount = 6, g2p3MaxCount = 2;
    int g3p1MaxCount = 2, g3q1MaxCount = 6, g3p2MaxCount = 5, g3p3MaxCount = 3;

    VGroup* vscene = new VSimpleGroup();
    makeSparkleFlameGroup(vscene, g1Center, g1p1MaxCount, g1p2MaxCount, g1p3MaxCount, g1q1MaxCount);  
    makeSparkleFlameGroup(vscene, g2Center, g2p1MaxCount, g2p2MaxCount, g2p3MaxCount, g2q1MaxCount);
    makeSparkleFlameGroup(vscene, g3Center, g3p1MaxCount, g3p2MaxCount, g3p3MaxCount, g3q1MaxCount);    
    return vscene;
}

void addStick(Group * scene, Material *material, Vector groupOrigin, float angle){
    
    float radius = 0.1, yMin = -6, yMax = 0.5f;
    Point cOrigin(0, 0, 0);
    Cylinder *cylinderStick1 = new Cylinder(cOrigin, radius, yMin, yMax, nullptr, material);
    Instance *instanceStick1 = new Instance(cylinderStick1);

    instanceStick1->rotate(Vector(0, 0, 1), angle);
    instanceStick1->translate(groupOrigin);
    scene->add(instanceStick1);

    Cylinder *cylinderStick2 = new Cylinder(cOrigin, 0.02, -8, -6, nullptr, material);
    Instance *instanceStick2 = new Instance(cylinderStick2);
    instanceStick2->rotate(Vector(0, 0, 1), angle);
    instanceStick2->translate(groupOrigin);
    scene->add(instanceStick2);
}
 
World makeSparkleSticks(){
    
    Vector group1Center = Vector(0, 4, -2);
    Vector group2Center = Vector(3, 1.5, 0);
    Vector group3Center = Vector(-2, 2, 0);
    float angleStick1 = 0; 
    float angleStick2 = -pi/10; 
    float angleStick3 = pi/12; 

    World world;
    
    Group* scene = new SimpleGroup();
    Texture *blacktex, *whitetex, *tealtex;
    blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    whitetex = new ConstantTexture(RGBColor::rep(1.0f));
    tealtex = new ConstantTexture(RGBColor(0, 0.1f, 0.1f));
    Material *lambertianStick = new LambertianMaterial(blacktex, whitetex);
    Material *backwall = new LambertianMaterial(tealtex, whitetex);

    /*
    PerlinTexture* perlinTex = new PerlinTexture(RGBColor(0, 0.15f, 0.15f), RGBColor::rep(0.0f));
    perlinTex->addOctave(0.5f, 5.0f);
    perlinTex->addOctave(0.25f, 10.0f);
    perlinTex->addOctave(0.125f, 20.0f);
    perlinTex->addOctave(0.125f, 40.0f);
    */
    //Material *backwall = new LambertianMaterial(perlinTex, whitetex);


    addStick(scene, lambertianStick, group1Center, angleStick1);
    addStick(scene, lambertianStick, group2Center, angleStick2);
    addStick(scene, lambertianStick, group3Center, angleStick3);
    
    scene->add(new InfinitePlane(Point(0.0f,0.0f,-3.f), Vector(0.f, 0.1f, 1.0f), nullptr, backwall));
    world.scene = scene;

    RGBColor intensity = RGBColor(0.886f, 0.345f, 0.133f);
    //world.light.push_back(new PointLight(Point(2, 4, 1), 15 * intensity));
    //world.light.push_back(new PointLight(Point(-2, 4, 1), 15 * intensity));
    world.light.push_back(new PointLight(Point(0, 4, 1), 25 * intensity));
    return world;
}

void renderFireworks(const char* filename, int numSamples=1) {

    Image img(400, 400);
    //Image img(1920, 1080);
   
    World world = makeSparkleSticks();

    VGroup *vscene = makeSparkleFlames();
    
    RayTraceFireIntegrator integrator(&world, vscene);

    PerspectiveCamera cam(Point(0, 0, 10), Vector(0, 0, -1), Vector(0, 1, 0), pi/3, pi/3);
    //DOFPerspectiveCamera dofcam(Point(0, 0, 10), Vector(0, 0, -1), Vector(0, 1, 0), pi/3, pi/3, 1.025f, 0.045f);
    
    Renderer engine(&cam, &integrator);
     if (numSamples>1)
        engine.setSamples(numSamples);
    engine.render(img);
    img.writePNG(filename);

}
}


void a_fire() {
    /*HRES*/
    renderFireworks("a9-1-hres.png", 10);
    /*LRES*/
    //renderFireworks("a9-1-lres.png", 2);
}