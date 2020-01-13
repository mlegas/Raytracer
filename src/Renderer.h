/** @file Renderer.h
 *  @brief Renderer class responsible for processing and showing the colour output from the raytracer functions.
 *
 *  This class contains the function used by each thread with an anti-aliasing technique.
 *  It is also responsible for initializing each major class such as Camera, Scene and ThreadManager.
 */

#include <glm/vec2.hpp>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

class Camera;
class Scene;
class ThreadManager;

class Renderer
{
private:
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Scene> m_scene;
    std::shared_ptr<ThreadManager> m_threadManager;

    std::chrono::system_clock::time_point m_deltaTime; ///< Used to calculate time taken to finish.
    glm::ivec2 m_windowSize;
    float m_fov; ///< Field of view.
    bool m_showStatus; ///< This boolean is used to stop other threads from displaying percentage progress.
    int m_samples; ///< Amount of rays per pixel, used for anti-aliasing.
    std::mutex m_mtx; ///< Mutex used to stop other threads in displaying progress.

    /** @brief Raytraces through a part of the screen, depending on the set interval.
     *  @param _startValue The start pixel X position for the interval.
     *  @param _interval The end pixel X position for the interval.
     *  @param _threadId Thread ID number, used for displaying its progress.
     */
    void MainLoop(int _startValue, int _interval, int _threadId);
public:
    /** @brief Constructs a renderer and sets the initial values to pass during Init() to class members.
     *  @param _windowSize The dimensions of the window.
     *  @param _interval The end pixel X position for the interval.
     *  @param _threadId Thread ID number, used for displaying its progress.
     */
    Renderer(glm::ivec2 _windowSize, float _fov, int _samples);
    /** @brief Initializes the class members with variables previously set in its constructor.
     *  @param _maxDepth The depth limit for reflection and transmission rays.
     */
	bool Init(int _maxDepth);
    /// @brief Starts the raytracing process.
    void Run();
};
