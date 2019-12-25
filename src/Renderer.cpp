#include <thread>
#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>
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

bool Renderer::Init()
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

    if (!m_threadManager->Init(m_windowSize))
    {
        return -1;
    }

    m_camera = std::make_shared<Camera>(m_windowSize, m_fov);
    m_scene = std::make_shared<Scene>();

    return true;
}

void Renderer::Run()
{
    m_deltaTime = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    std::vector<int> startValues;

    startValues.push_back(0);

    for (uint values = 0; values < m_threadManager->GetThreadsAmount() - 1; values++)
    {
        startValues.push_back(m_threadManager->GetIntervals().at(values));
    }

    for (uint t = 0; t < m_threadManager->GetThreadsAmount(); t++)
    {
        m_threadManager->m_threads.push_back(std::thread(&Renderer::MainLoop, this, startValues.at(t), m_threadManager->GetIntervals().at(t), t));
    }

    for (uint t = 0; t < m_threadManager->GetThreadsAmount(); t++)
    {
        m_threadManager->m_threads.at(t).join();
    }

    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

    std::cout << "Finished drawing." << std::endl;
    std::cout << "Time spent raytracing: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s" << std::endl;

    MCG::ShowAndHold();
    MCG::Cleanup();
}

void Renderer::MainLoop(int _startValue, int _interval, int _threadId)
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
                pixelColour = pixelColour + Raytracer::RayTrace(m_camera->CreateRay(currentPixel), m_scene, 0);
            }

            pixelColour = glm::vec3(pixelColour.x / m_samples, pixelColour.y / m_samples, pixelColour.z / m_samples);

            MCG::DrawPixel(currentPixelI, pixelColour);
        }

        int percentDone = ((static_cast<float>(x - _startValue)) / static_cast<float>(_interval - _startValue)) * 100.0f;
        m_threadManager->SetPercentDone(_threadId, percentDone + 1);

        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_deltaTime).count() > 500)
        {
            std::system("CLS");

            int total = 0;

            for (int t = 0; t < m_threadManager->GetThreadsAmount(); t++)
            {
                int percent = m_threadManager->GetPercentDone(t);
                total += percent;

                m_mtx.lock();
                std::cout << "Thread #" << t << ": " << percent << "% finished" << std::endl;
                m_mtx.unlock();
            }

            total /= m_threadManager->GetThreadsAmount();

            m_mtx.lock();
            std::cout << "Total percent done: " << total << "%" << std::endl;
            m_mtx.unlock();

            m_deltaTime = std::chrono::system_clock::now();
        }

    }
}
