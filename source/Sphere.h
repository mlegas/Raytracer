#pragma once
#include <memory>

class Ray;

class Sphere
{
public:
	glm::vec3 ShadePixel(std::shared_ptr<Ray> _ray, glm::vec3 _intersectionPoint)
	{
		return glm::vec3(1, 1, 1);
	}

	Sphere();
	~Sphere();
};
