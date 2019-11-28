#include <glm/ext.hpp>
#include <vector>
#include <memory>

struct IntersectionData
{
	bool m_intersection;
	std::vector<glm::vec3> m_points;
};

class Sphere;

class Ray
{
private:
	glm::vec3 m_origin;
	glm::vec3 m_direction;
	glm::vec3 m_normalizedDirection;
	float m_lengthOnLine;
public:
	Ray(glm::vec3 _origin, glm::vec3 _direction);
	glm::vec3 ClosestPoint(glm::vec3 _queryPoint);
	std::shared_ptr<IntersectionData> SphereIntersection(std::shared_ptr<Sphere> _sphere);
	glm::vec3 NormalOfSphere(std::shared_ptr<Sphere> _sphere, glm::vec3 _intersectionPoint);
};

