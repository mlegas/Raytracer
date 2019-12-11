    #include <thread>
#include <iostream>
#include <random>
#include <chrono>
#include "Camera.h"
#include "Raytracer.h"
#include "Scene.h"
#include "MCG_GFX_Lib.h"
#include "Renderer.h"
#include "ThreadManager.h"

Renderer::Renderer(glm::ivec2 _windowSize, float _fov, int _samples)
{
    m_windowSize = _windowSize;
    m_fov = _fov;
    m_samples = _samples;
}

bool Renderer::init()
{   
    /** Call MCG::Init to initialise and create your window
     *  Tell it what size you want the window to be */
    if( !MCG::Init( m_windowSize ) )
    {
        /** We must check if something went wrong
         *  (this is very unlikely) */
        return -1;
    }

    /** Sets every pixel to the same colour
     * parameters are RGBA, numbers are from 0 to 255 */
    MCG::SetBackground( glm::ivec3(255,255,255) );

    m_threadManager = std::make_shared<ThreadManager>();

    if (!m_threadManager->init(m_windowSize))
    {
        return -1;
    }

    m_camera = std::make_shared<Camera>(m_windowSize, m_fov);
    m_raytracer = std::make_shared<Raytracer>();
    m_scene = std::make_shared<Scene>();

    return true;
}

void Renderer::run()
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    std::vector<int> startValues;

    startValues.push_back(0);

    for (uint values = 0; values < m_threadManager->m_threadsAmount - 1; values++)
    {
        startValues.push_back(m_threadManager->m_intervals.at(values));
    }

    for (uint t = 0; t < m_threadManager->m_threadsAmount; t++)
    {
        m_threadManager->m_threads.push_back(std::thread(&Renderer::goThroughPixels, this, startValues.at(t), m_threadManager->m_intervals.at(t), t));
    }

    for (uint t = 0; t < m_threadManager->m_threadsAmount; t++)
    {
        m_threadManager->m_threads.at(t).join();
    }

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    std::cout << "Finished drawing." << std::endl;
    std::cout << "Time spent raytracing: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s" << std::endl;

    MCG::ShowAndHold();
    MCG::Cleanup();
}

void Renderer::goThroughPixels(int _startValue, int _interval, int _threadId)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-0.5f,0.5f);

    for (int x = _startValue; x < _interval; x++)
    {
        for (int y = 0; y < m_windowSize.y; y++)
        {
            glm::vec3 pixelColour = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::ivec2 currentPixelI = glm::ivec2(x, y);

            for (int i = 0; i < m_samples; i++)
            {
                float sample = distribution(generator);
                glm::vec2 currentPixel = glm::vec2(static_cast<float>(x) + sample, static_cast<float>(y) + sample);
                pixelColour = pixelColour + m_raytracer->rayTrace(m_camera->createRay(currentPixel), m_scene);
            }

            pixelColour = glm::vec3(pixelColour.x / m_samples, pixelColour.y / m_samples, pixelColour.z / m_samples);

            MCG::DrawPixel(currentPixelI, pixelColour, m_threadManager->m_mtx);
        }

        int percentDone = ((static_cast<float>(x - _startValue)) / static_cast<float>(_interval - _startValue)) * 100.0f;

        if (percentDone % 10 == 0 && percentDone > 0)
        {
            m_threadManager->m_mtx.lock();

            std::cout << "Thread #" << _threadId << ": " << percentDone << "% finished" << std::endl;

            m_threadManager->m_mtx.unlock();
        }
    }
}
