/** @file Main.cpp
 *	@brief The main function, responsible for setting the raytracer before initialization.
 */

#include "Renderer.h"
#include <iostream>
#include <memory>

/// Clear the console in different ways depending on used OS.
#ifdef _WIN32
#define Clear system("CLS");
#else
#define Clear system("clear");
#endif

int main()
{
    glm::ivec2 windowSize = glm::ivec2(800, 800); ///< Sets the initial size of the window.
    float fov = 60.0f; ///< Sets the default FOV.
    int samples = 4; ///< Sets the default amount of samples for anti-aliasing.
    int maxDepth = 5; ///< Sets the default max depth for reflecting rays.

	/// This menu has been reused from a previous MCG assignment and modified.
	bool quitMenu = false;
	int choice;
	
	while (!quitMenu) ///< Shows the menu until the user quits it.
	{
		bool correctChoice = false;
		while (!correctChoice) ///< Asks for user input until a correct choice has been made.
		{
			Clear;
			std::cout << "=== RAY TRACER ===\n";
			std::cout << "Change a value and/or run the raytracer:\n";
			std::cout << "1. Window size: " << windowSize.x << "x" << windowSize.y << "\n";
			std::cout << "2. FOV: " << fov << "\n";
			std::cout << "3. Samples: " << samples << "\n";
			std::cout << "4. Max depth: " << maxDepth << "\n";
			std::cout << "5. Run the raytracer\n";
			std::cout << "0. Quit\n\n";

            std::cin >> choice;
			switch (choice)
			{
				case 1:
				{
					correctChoice = true;
					bool correctValue = false;
					int value = 0;
					
					while (!correctValue)
					{
						std::cout << "X: ";
						std::cin >> value;
						
						if (value < 32) /**< The limit of 32 is used as the multi-threading technique bases on 
										 *   dividing the screen area into "slices" for each thread using the screen's width.
										 *   32 is the current limit of cores in a single CPU as of 01/2020. */
						{
							Clear;
							std::cout << "The width of the window must be higher than 10.\n\n";
						}
						
						else 
						{
							correctValue = true;
							windowSize.x = value;
						}
					}
					
					correctValue = false;
					
					while (!correctValue)
					{
						std::cout << "Y: ";
						std::cin >> value;
						
						if (value < 1)
						{
							Clear;
							std::cout << "The height of the window must be higher than 0.\n\n";
						}
						
						else 
						{
							correctValue = true;
							windowSize.y = value;
						}
					}
					
					break;
				}
				
				case 2:
				{
					correctChoice = true;
					bool correctValue = false;
					float value = 0.0f;
					
					while (!correctValue)
					{
						std::cout << "FOV: ";
						std::cin >> value;
						
						if (value < 10.0f)
						{
							Clear;
							std::cout << "The FOV must be higher than 10.\n\n";
						}
						
						else 
						{
							correctValue = true;
							fov = value;
						}
					}

					break;
				}
				
				case 3:
				{
					correctChoice = true;
					bool correctValue = false;
					int value = 0;
					
					while (!correctValue)
					{
						std::cout << "Samples: ";
						std::cin >> value;
						
						if (value < 1)
						{
							Clear;
							std::cout << "The amount of samples must be higher than 0.\n\n";
						}
						
						else 
						{
							correctValue = true;
							samples = value;
						}
					}

					break;
				}
				
				case 4:
				{
					correctChoice = true;
					bool correctValue = false;
					int value = 0;
					
					while (!correctValue)
					{
						std::cout << "Max depth: ";
						std::cin >> value;
						
						if (value < 1)
						{
							Clear;
							std::cout << "The maximum depth must be higher than 0.\n\n";
						}
						
						else 
						{
							correctValue = true;
							maxDepth = value;
						}
					}

					break;
				}
				
				case 5:
				{
					correctChoice = true;
					
					/// Constructs a renderer with the specified values.
					std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(windowSize, fov, samples);

					if (!renderer->Init(maxDepth)) ///< Initializes the renderer with the scene.
					{
						/// MCG unable to initialize or CPU thread information obscured, quit.
						std::cout << "Renderer failed to initialize.\n\n";
						return -1;
					}
					
					renderer->Run(); ///< Runs the raytracer.
					break;
				}
				
				case 0:
				{
					Clear;
					correctChoice = true;
					quitMenu = true;
					break;
				}
				
				default:
				{
					Clear;
					std::cout << "Incorrect input, please try again.\n\n";
					break;
				}
			}
		}
	}

	return 0;
}
