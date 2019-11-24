#include <glm/ext.hpp>
#include <memory>

class Ray;

class Sphere
{
private:
	glm::vec3 m_position;
	float m_radius;
public:
	glm::vec3 ShadePixel(std::shared_ptr<Ray> _ray, glm::vec3 _intersectionPoint)
	{
		return glm::vec3(1, 1, 1);
	}

	Sphere();
	~Sphere();
};
