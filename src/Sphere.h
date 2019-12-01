#include "Object.h"
#include <glm/ext.hpp>
#include <memory>

class Ray;

class Sphere : public Object
{
private:
	float m_radius;
public:
	glm::vec3 shadePixel(std::shared_ptr<Ray> _ray, glm::vec3 _intersectionPoint);
	float getRadius();
	Sphere(glm::vec3 _position, float _radius);
	~Sphere();
};
