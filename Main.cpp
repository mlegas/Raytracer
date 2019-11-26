#include <iostream>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>
#include <memory>
#include "Camera.h"
#include "Raytracer.h"

int main()
{
	SDL_Renderer *renderer;
	SDL_Window *window;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		// Something went very wrong in initialisation, all we can do is exit
	{
		std::cout << "MCG Framework: Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return false;
	}

	glm::ivec2 windowSize = glm::ivec2(800, 600);

	int winPosX = 1000;
	int winPosY = 300;
	window = SDL_CreateWindow("Raytracer",
		winPosX, winPosY,
		windowSize.x, windowSize.y,
		SDL_WINDOW_SHOWN);

	if (!window)
	{
		std::cout << "Something went very wrong, cannot create the SDL window" << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{
		std::cout << "Whoops! Something went very wrong, cannot obtain SDL rendering context" << std::endl;
		return false;
	}

	std::shared_ptr<Camera> camera;
	std::shared_ptr<Raytracer> raytracer;
	glm::ivec2 currentPixel;

	for (int x = 0; x < windowSize.x; x++)
	{
		for (int y = 0; y < windowSize.y; y++)
		{
			currentPixel = glm::ivec2(x, y);

			glm::vec3 pixelColour = raytracer->RayTrace(camera->CreateRay(currentPixel));

			// Set the colour for drawing
			SDL_SetRenderDrawColor(renderer, pixelColour.r, pixelColour.g, pixelColour.b, 255);
			// Draw our pixels
			SDL_RenderDrawPoint(renderer, currentPixel.x, currentPixel.y);
		}
	}
}
