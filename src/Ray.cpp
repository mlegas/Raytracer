#include "Ray.h"
#include <memory>

Ray::Ray(glm::vec3 _origin, glm::vec3 _direction)
{
    m_origin = _origin;
    m_direction = _direction;
}

glm::vec3 Ray::GetOrigin()
{
    return m_origin;
}

glm::vec3 Ray::GetDirection()
{
    return m_direction;
}
