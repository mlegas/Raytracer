#include <glm/ext.hpp>
#include <memory>

class Ray;

class Camera
{
private:
	glm::mat4 view;
	glm::mat4 projection;
	
public:
	std::shared_ptr<Ray> CreateRay(glm::ivec2 _pixelCoords);
	Camera();
	~Camera();
};

