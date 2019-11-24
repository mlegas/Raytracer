#include <glm/ext.hpp>
#include <memory>

class Ray
{
private:
	glm::vec3 m_origin;
	glm::vec3 m_direction;
	glm::vec3 m_normalizedDirection;
	float m_lengthOnLine;
public:
	Ray();
	glm::vec3 GetOrigin();
	glm::vec3 GetDirection();
	glm::vec3 ClosestPoint(std::shared_ptr<Ray> _ray, glm::vec3 _queryPoint);

};

