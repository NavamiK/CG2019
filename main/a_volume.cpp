
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>


#include <rt/cameras/perspective.h>
#include <rt/solids/quad.h>
#include <rt/groups/simplegroup.h>
#include <rt/materials/dummy.h>

#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>
#include <rt/lights/projectivelight.h>

#include <rt/integrators/volumetrace_a.h>
#include <rt/integrators/volumetrace_b.h>
#include <rt/integrators/volumetrace_c.h>
#include <rt/integrators/raytrace.h>

using namespace rt;

namespace {

enum FogType {
        NO_FOG,
        UNIFORM_AMBIENT,
        UNIFORM_TRUELIGHT,
        PERLIN_TRUELIGHT
    };

void makeBox(Group* scene, const Point& aaa, const Vector& forward, const Vector& left, const Vector& up, CoordMapper* texMapper, Material* material) {
    scene->add(new Quad(aaa, left, forward, texMapper, material));
    scene->add(new Quad(aaa, forward, up, texMapper, material));
    scene->add(new Quad(aaa, up, left, texMapper, material));
    Point bbb = aaa + forward + left + up;
    scene->add(new Quad(bbb, -forward, -left, texMapper, material));
    scene->add(new Quad(bbb, -up, -forward, texMapper, material));
    scene->add(new Quad(bbb, -left, -up, texMapper, material));
}

void makeWalls(Group* scene, float scale, CoordMapper* texMapper, Material* material) {
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(550.f, 000.f, 000.f)*scale, texMapper, material)); //floor
    scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(-550.f, 000.f, 000.f)*scale, texMapper, material)); //ceiling
    scene->add(new Quad(Point(000.f, 000.f, 560.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(550.f, 000.f, 000.f)*scale, texMapper, material)); //back wall
    scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, texMapper, material)); //right wall
    scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, -550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, texMapper, material)); //left wall
}

void renderCornellboxA(float scale, const char* filename, FogType fogType) {

    Image img(400, 400);
    World world;
    Group* scene = new SimpleGroup();
    world.scene = scene;

    PerspectiveCamera cam(Point(278*scale, 273*scale, -800*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);

    DummyMaterial* mat = new DummyMaterial();

    // walls
    makeWalls(scene, scale, nullptr, mat);

    //short box
    makeBox(scene, Point(082.f, 000.1f, 225.f)*scale, Vector(158.f, 000.f, 047.f)*scale, Vector(048.f, 000.f, -160.f)*scale, Vector(000.f, 165.f, 000.f)*scale, nullptr, mat);

    //tall box
    makeBox(scene, Point(265.f, 000.1f, 296.f)*scale, Vector(049.f, 000.f, 160.f)*scale, Vector(158.f, 000.f, -049.f)*scale, Vector(000.f, 330.f, 000.f)*scale, nullptr, mat);

    //point light
    world.light.push_back(new PointLight(Point(288*scale,529.99f*scale,279.5f*scale),RGBColor::rep(40000.0f*scale*scale)));
    world.light.push_back(new PointLight(Point(490*scale,329.99f*scale,279.5f*scale),RGBColor(60000.0f*scale*scale,0,0)));
    world.light.push_back(new PointLight(Point(40*scale,329.99f*scale,279.5f*scale),RGBColor(0,60000.0f*scale*scale,0)));

    if(fogType == FogType::UNIFORM_AMBIENT){
        VolumeTracingAIntegrator integratorA(&world);
        Renderer engineA(&cam, &integratorA);
        engineA.render(img);
        img.writePNG(filename);
    }
    else if (fogType == FogType::UNIFORM_TRUELIGHT){
        VolumeTracingBIntegrator integratorB(&world);
        Renderer engineB(&cam, &integratorB);
        engineB.render(img);
        img.writePNG(filename);
    }
    else if (fogType == FogType::PERLIN_TRUELIGHT){
        VolumeTracingCIntegrator integratorC(&world);
        Renderer engineC(&cam, &integratorC);
        engineC.render(img);
        img.writePNG(filename);
    }else{
        RayTracingIntegrator integrator(&world);
        Renderer engine(&cam, &integrator);
        engine.render(img);
        img.writePNG(filename);
    }
}
}


void a_volume() {
    //This is for testing different scenarios of Assignment 8.4 
    renderCornellboxA(0.001f, "a8-3.png", FogType::NO_FOG);
    renderCornellboxA(0.001f, "a8-4.png", FogType::UNIFORM_AMBIENT);
    renderCornellboxA(0.001f, "a8-5.png", FogType::UNIFORM_TRUELIGHT);
    renderCornellboxA(0.001f, "a8-6.png", FogType::PERLIN_TRUELIGHT);
}