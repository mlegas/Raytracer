#include <glm/ext.hpp>
#include <memory>

class Ray;

class Raytracer
{
public:
	glm::vec3 RayTrace(std::shared_ptr<Ray> _ray);

	Raytracer();
	~Raytracer();
};

