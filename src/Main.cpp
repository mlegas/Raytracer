#include <iostream>
#include <memory>
#include <random>
#include <thread>
#include "MCG_GFX_Lib.h"
#include "Camera.h"
#include "Raytracer.h"
#include "Scene.h"
#include "Renderer.h"
#include "Texture.h"

int main()
{
    glm::ivec2 windowSize = glm::ivec2(800, 800);
    float fov = 60.0f;
    int samples = 1;

    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(windowSize, fov, samples);

    if (!renderer->Init())
    {
        // MCG unable to initialize or (if enabled) CPU thread information obscured
        return -1;
    }

    //Texture texture("/home/maciej/Pobrane/tvpis85ac58.jpg");

    renderer->Run();


	return 0;
}
