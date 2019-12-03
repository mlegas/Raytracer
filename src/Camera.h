#include <glm/ext.hpp>
#include <memory>

class Ray;

class Camera
{
private:
    float m_aspectRatio;
    float m_fovFactor;
    glm::ivec2 m_windowSize;
    glm::mat4 m_view;
	
public:
    Ray CreateRay(glm::ivec2 _pixelCoords);
    Camera(glm::ivec2 _windowSize, float _fov);
	~Camera();
};

