/** @file Plane.cpp
 *  @brief Implementation of functions for the Ray class.
 */

#include "Ray.h"
#include <glm/ext.hpp>
#include <memory>

Ray::Ray(glm::vec3 _origin, glm::vec3 _direction)
{
    m_origin = _origin;
    m_direction = glm::normalize(_direction); ///< Normalizes the ray's direction to ensure a consistent approach in calculations.
}

glm::vec3 Ray::GetOrigin()
{
    return m_origin;
}

glm::vec3 Ray::GetDirection()
{
    return m_direction;
}
