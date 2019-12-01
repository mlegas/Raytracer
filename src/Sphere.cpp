#include "Sphere.h"

glm::vec3 Sphere::shadePixel(std::shared_ptr<Ray> _ray, glm::vec3 _intersectionPoint)
{
    return glm::vec3(255.0f, 255.0f, 255.0f);
}

float Sphere::getRadius()
{
	return m_radius;
}

Sphere::Sphere(glm::vec3 _position, float _radius)
{
	m_position = _position;
	m_radius = _radius;
}


Sphere::~Sphere()
{
}
