#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <memory>

class Ray;

class Camera
{
private:
    float m_aspectRatio;
    float m_fovFactor;
    glm::vec2 m_windowSize;
    glm::mat4 m_view;
	
public:
    std::shared_ptr<Ray> CreateRay(glm::vec2 _pixelCoords);
    Camera(glm::vec2 _windowSize, float _fov);
	~Camera();
};

