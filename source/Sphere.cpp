#include "Sphere.h"

glm::vec3 Sphere::shadePixel(std::shared_ptr<Ray> _ray, glm::vec3 _intersectionPoint)
{
		return glm::vec3(1, 1, 1);
}

float Sphere::getRadius()
{
	return m_radius;
}

Sphere::Sphere(glm::vec3 _position, float _radius)
{
}


Sphere::~Sphere()
{
}
