/** @file Renderer.cpp
 *	@brief Implementation of functions for the Renderer class.
 */

#include "Renderer.h"
#include "Camera.h"
#include "MCG_GFX_Lib.h"
#include "Raytracer.h"
#include "Scene.h"
#include "ThreadManager.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <thread>

/** The lines below change the used command for cleaning the terminal
 *  depending on used operating system. */
#ifdef _WIN32
#define Clear system("CLS");
#else
#define Clear system("clear");
#endif

Renderer::Renderer(glm::ivec2 _windowSize, float _fov, int _samples)
{
    m_windowSize = _windowSize;
    m_fov = _fov;
    m_samples = _samples;
    m_showStatus = false;
}

bool Renderer::Init(int _maxDepth)
{   
    /// Initializes the SDL window with the specified window size.
    if (!MCG::Init(m_windowSize))
    {
		/// Initialization failed, return.
        return -1;
    }

    /// Colours the window black.
    MCG::SetBackground( glm::ivec3(0,0,0) );

    m_threadManager = std::make_shared<ThreadManager>();

	/// Initializes the thread manager, which is responsible for passing the raytracing function to each thread.
    if (!m_threadManager->Init(m_windowSize))
    {
        return -1;
    }

	/// Creates a camera, which will use the specified FOV and window size for the viewing matrix.
    m_camera = std::make_shared<Camera>(m_windowSize, m_fov);
	/// Initializes the scene and sets the maximum depth for reflection and transmission rays.
    m_scene = std::make_shared<Scene>(_maxDepth);

    return true;
}

void Renderer::Run()
{
    /// Starts a timer.
    m_deltaTime = std::chrono::system_clock::now();
    /// Set a start time variable to compare the finish time with.
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    std::vector<int> startValues; ///< Vector used to store values from which each interval starts.

    startValues.push_back(0); ///< Sets 0 as first start value.

    for (int values = 0; values < m_threadManager->GetThreadsAmount() - 1; values++)
    {
        /// Sets start values to be each interval value except for the last one (as we cannot start at the end.
        startValues.push_back(m_threadManager->GetIntervals().at(values));
    }

    for (int threadId = 0; threadId < m_threadManager->GetThreadsAmount(); threadId++)
    {
        /** Pushes back a thread executing the MainLoop() function, with a set start pixel value
         * and interval to finish drawing at, and a thread ID identifying the thread. */
        m_threadManager->m_threads.push_back(std::thread(&Renderer::MainLoop, this, startValues.at(threadId), m_threadManager->GetIntervals().at(threadId), threadId));
    }

    for (int t = 0; t < m_threadManager->GetThreadsAmount(); t++)
    {
        /// Wait for each thread to finish drawing before continuing.
        m_threadManager->m_threads.at(t).join();
    }

    /// Sets a finish time.
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

    std::cout << "Finished drawing.\n";
    /// Calculate the time spent raytracing from subtracting the finish time from start time.
    std::cout << "Time spent raytracing: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0f << "s\n";
	std::cout << "Press TAB while focused on the raytracer window to return to the menu.\n\n";

    /// Show the render.
    MCG::ShowAndHold();
    /// Destroy the window.
    MCG::Cleanup();
    /// Clear the terminal.
	Clear;
}

void Renderer::MainLoop(int _startValue, int _interval, int _threadId)
{
    std::default_random_engine generator;
    /// Random number generator used for randomizing the position of a sample ray in a pixel.
    std::uniform_real_distribution<float> distribution(-0.5f,0.5f);

    /** This loop raytraces starting from a set start X value until a set end X value (interval),
     *  therefore each thread raytraces a vertical part of the window. */
    for (int x = _startValue; x < _interval; x++)
    {
        for (int y = 0; y < m_windowSize.y; y++)
        {
            glm::vec3 pixelColour = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::ivec2 currentPixelI = glm::ivec2(x, y);

            /// Raytrace a pixel for a set amount of samples for anti-aliasing.
            for (int i = 0; i < m_samples; i++)
            {
                float sample = distribution(generator); ///< Sets how far from the middle of the pixel the ray should trace.
                /// Add the offset to the current pixel position.
                glm::vec2 currentPixel = glm::vec2(static_cast<float>(x) + sample, static_cast<float>(y) + sample);
                /// Raytrace the current pixel position through the scene. The integer "0" sets the initial ray depth to 0.
                glm::vec3 raytracedColour = Raytracer::RayTrace(m_camera->CreateRay(currentPixel), m_scene, 0);
                /** As all colour calculations are in the range between 0 and 1,
                 *  we need to convert the returned colour value to the RGB range of 0-255. */
                raytracedColour = glm::vec3(glm::clamp((raytracedColour.x * 255.0f), 0.0f, 255.0f),
                                   glm::clamp((raytracedColour.y * 255.0f), 0.0f, 255.0f),
                                   glm::clamp((raytracedColour.z * 255.0f), 0.0f, 255.0f));

                pixelColour = pixelColour + raytracedColour; ///< Sum the ray traced colour to a total.
            }
            /// Divide the sum by the amount of samples to receive an average colour.
            pixelColour = glm::vec3(pixelColour.x / m_samples, pixelColour.y / m_samples, pixelColour.z / m_samples);
            /// Draw the pixel colour on the window.
            MCG::DrawPixel(currentPixelI, pixelColour);
        }

        /// Calculate the progress of the thread by checking the current X value.
        int percentDone = ((static_cast<float>(x - _startValue)) / static_cast<float>(_interval - _startValue)) * 100.0f;
        /** Set the progress in the ThreadManager's vector. Although multiple threads may access the vector
         *  at the same time, they are never writing to the same position. */
        m_threadManager->SetPercentDone(_threadId, percentDone + 1);

        /// Store the current time.
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

        /// Display the overall progress after every 100ms passed.
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_deltaTime).count() > 100 && !m_showStatus)
        {
            m_mtx.lock(); ///< Locks the mutex.

            /** This if statement's role is to block other threads from displaying the progress in the terminal,
             *  as only one thread at a time can access the if statement below due to the mutex lock. Therefore,
             *  when the mutex unlocks, the m_showStatus variable is set to true, blocking other threads from accessing
             *  the if statement above.
             *
             *  Of course, there might be a situation where both threads happen to be checking the same if
             *  statement, though such a situation has not been witnessed during debugging. */
			if (!m_showStatus) 
			{
                m_showStatus = true;
			}
			
			m_mtx.unlock();
			
            /** This if statement is here to block any other threads that might have somehow entered the starting if statement
             *  from displaying the progress information, with the hope that the thread displaying the information
             *  has finished displaying the progress, therefore setting the m_showStatus to false at the end.
             *
             *  During debugging however, no multiple displays of the progress have been detected. */
			if (m_showStatus)
			{
                Clear; ///< Clear the terminal.

                int total = 0; ///< Sum of progress.

                for (int threadId = 0; threadId < m_threadManager->GetThreadsAmount(); threadId++)
				{
                    /// Return the progress from ThreadManager.
                    int percent = m_threadManager->GetPercentDone(threadId);
                    total += percent; ///< Sum the progress.

                    /// Display the progress of the currently evaluated thread.
                    std::cout << "Thread #" << threadId + 1 << ": " << percent << "% finished" << std::endl;
				}

                /// Divide the total progress by the amount of threads.
				total /= m_threadManager->GetThreadsAmount();

				std::cout << "Total percent done: " << total << "%" << std::endl;

                /// Reset the progress timer.
				m_deltaTime = std::chrono::system_clock::now();
                /// Stop showing progress.
				m_showStatus = false;
			}
        }

    }
}
