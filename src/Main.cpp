#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include "MCG_GFX_Lib.h"
#include "Camera.h"
#include "Raytracer.h"
#include "Scene.h"

int main()
{
    glm::ivec2 windowSize = glm::ivec2(800, 800);

    /** Call MCG::Init to initialise and create your window
     *  Tell it what size you want the window to be */
    if( !MCG::Init( windowSize ) )
    {
        /** We must check if something went wrong
         *  (this is very unlikely) */
        return -1;
    }

    /** Sets every pixel to the same colour
     * parameters are RGBA, numbers are from 0 to 255 */
    MCG::SetBackground( glm::ivec3(255,255,255) );

    float fov = 90.0f;

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(windowSize, fov);
	std::shared_ptr<Raytracer> raytracer = std::make_shared<Raytracer>();
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	glm::ivec2 currentPixel;

	for (int x = 0; x < windowSize.x; x++)
	{
		for (int y = 0; y < windowSize.y; y++)
		{
			currentPixel = glm::ivec2(x, y);

			glm::vec3 pixelColour = raytracer->RayTrace(camera->CreateRay(currentPixel), scene);

            MCG::DrawPixel(currentPixel, pixelColour);
		}
	}

	std::cout << "Finished drawing" << std::endl;

    MCG::ShowAndHold();
    MCG::Cleanup();
	return 0;
}
