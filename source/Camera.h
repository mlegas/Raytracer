#include <glm/ext.hpp>
#include <memory>

class Ray;

class Camera
{
private:
	glm::ivec2 m_windowSize;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	
public:
	std::shared_ptr<Ray> CreateRay(glm::ivec2 _pixelCoords);
	Camera(glm::ivec2 _windowSize);
	~Camera();
};

