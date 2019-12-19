#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <memory>
#include <mutex>
#include <vector>
#include <thread>
#include <glm/vec2.hpp>

class Camera;
class Raytracer;
class Scene;

struct ThreadManager;

class Renderer
{
private:
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Raytracer> m_raytracer;
    std::shared_ptr<Scene> m_scene;
    std::shared_ptr<ThreadManager> m_threadManager;

    glm::ivec2 m_windowSize;
    float m_fov;
    int m_samples;

    void MainLoop(int _startValue, int _interval, int _threadId);
public:
    Renderer(glm::ivec2 _windowSize, float _fov, int _samples);
    bool Init();
    void Run();
};

#endif
