#include "Ray.h"
#include <memory>

glm::vec3 Ray::ClosestPoint(std::shared_ptr<Ray> _ray, glm::vec3 _queryPoint)
{
	m_normalizedDirection = glm::normalize(_ray->GetDirection());
	m_lengthOnLine = glm::dot((_queryPoint - _ray->GetOrigin()), m_normalizedDirection);
	glm::vec3 closestPoint = _ray->GetOrigin() + (m_lengthOnLine * m_normalizedDirection);
	return closestPoint;
}

glm::vec3 Ray::GetOrigin()
{
	return m_origin;
}
glm::vec3 Ray::GetDirection()
{
	return m_direction;
}

Ray::Ray()
{
}
