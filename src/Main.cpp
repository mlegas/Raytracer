#include <iostream>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>
#include <memory>
#include "Camera.h"
#include "Raytracer.h"
#include "Scene.h"

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

	std::shared_ptr<Camera> camera = std::make_shared<Camera>(windowSize);
	std::shared_ptr<Raytracer> raytracer = std::make_shared<Raytracer>();
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	glm::ivec2 currentPixel;

	for (int x = 0; x < windowSize.x; x++)
	{
		for (int y = 0; y < windowSize.y; y++)
		{
			currentPixel = glm::ivec2(x, y);

			glm::vec3 pixelColour = raytracer->RayTrace(camera->CreateRay(currentPixel), scene);

			// Set the colour for drawing
			SDL_SetRenderDrawColor(renderer, pixelColour.r, pixelColour.g, pixelColour.b, 255);
			// Draw pixels
			SDL_RenderDrawPoint(renderer, currentPixel.x, currentPixel.y);
		}
	}

	std::cout << "Finished drawing" << std::endl;
	// Show

	// This tells the renderer to actually show its contents to the screen
	// This is specific to the SDL drawing commands. When we start with OpenGL we will need to use a different command here
	// This is to do with something called 'double buffering', where we have an off-screen buffer that we draw to and then swap once we finish (this function is the 'swap')
	SDL_RenderPresent( renderer );




	// Hold

	// We are now preparing for our main loop (also known as the 'game loop')
	// This loop will keep going round until we exit from our program by changing the bool 'go' to the value false
	// This loop is an important concept and forms the basis of most games you'll be writing
	// Within this loop we generally do the following things:
	//   * Check for input from the user (and do something about it!)
	//   * Update our world
	//   * Draw our world
	// We will come back to this in later lectures
	bool go = true;
	while( go )
	{

		// Here we are going to check for any input events
		// Basically when you press the keyboard or move the mouse, the parameters are stored as something called an 'event'
		// SDL has a queue of events
		// We need to check for each event and then do something about it (called 'event handling')
		// the SDL_Event is the datatype for the event
		SDL_Event incomingEvent;
		// SDL_WaitEvent will check if there is an event in the queue
		// If there's nothing in the queue it will sit and wait around for an event to come along (there are functions which don't wait which can be useful too!)
		// When there is an event, the function will fill the 'incomingEvent' we have given it as a parameter with the event data
		SDL_WaitEvent( &incomingEvent );
		switch( incomingEvent.type )
		{
		case SDL_KEYUP:
			// The event type is SDL_KEYUP
			// This means that the user has released a key
			// Let's figure out which key they pressed

			switch( incomingEvent.key.keysym.sym ) /**< The cases in this switch have been modified to allow the user to
												    *   return to the menu, so that he does not need to relaunch the program
													*   each time he wishes to draw something else. */
			{
			case SDLK_TAB: ///< This is the TAB key.
				go = false; ///< This line breaks the loop.
				break;
			}

			// If you want to learn more about event handling and different SDL event types, see:
			// https://wiki.libsdl.org/SDL_Event
			// and also: https://wiki.libsdl.org/SDL_EventType
			// but don't worry, we'll be looking at handling user keyboard and mouse input soon
		}



	}
	return 0;
}
