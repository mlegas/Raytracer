#include "Ray.h"
#include <memory>

Ray::Ray(RayType _rayType, glm::vec3 _origin, glm::vec3 _direction)
{
    m_rayType = _rayType;
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

RayType Ray::getType()
{
    return m_rayType;
}
