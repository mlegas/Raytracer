#include "Ray.h"
#include <memory>

Ray::Ray(glm::vec3 _origin, glm::vec3 _direction)
{
    m_origin = _origin;
    m_direction = _direction;
}

glm::vec3 Ray::getOrigin()
{
    return m_origin;
}

glm::vec3 Ray::getDirection()
{
    return m_direction;
}
