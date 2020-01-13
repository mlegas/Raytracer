/** @file Plane.cpp
 *  @brief Implementation of functions for the Plane class.
 */

#include "Plane.h"
#include "Ray.h"
#include <glm/ext.hpp>

Plane::Plane(glm::vec3 _position, glm::vec3 _normal, std::shared_ptr<Material> _material)
{
    m_position = _position;
    m_normal = _normal;
    m_material = _material;
}

std::shared_ptr<IntersectionData> Plane::Intersect(std::shared_ptr<Ray> _ray)
{
    float denominator = glm::dot(m_normal, _ray->GetDirection());
    float t;

    /** Check if the dot product of the normal and ray's direction is above 0 (denominator in the equation used for solving t),
     *  meaning that the ray is not parallel to the plane.
     *  Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection */
    if (denominator > 0.000001f)
    {
        glm::vec3 originToPlane = m_position - _ray->GetOrigin(); ///< Vector from the ray's origin to the plane's position.
        t = glm::dot(originToPlane, m_normal) / denominator; ///< Calculate the distance from the equation.

        if (t < 0.0f) ///< If below 0, the intersection happened behind the ray's origin, therefore we discard the intersection.
        {
            return std::make_shared<IntersectionData>(false);
        }

        /// Set the intersection data and return it.
        float distance = t;
        glm::vec3 point = _ray->GetOrigin() + _ray->GetDirection() * t; ///< Set the intersection point using the ray's equation.
        return std::make_shared<IntersectionData>(true, distance, point, -m_normal); ///< The intersection normal can be just set to the negative of the plane's normal.
    }

    /// Return false if the ray is parallel to the plane.
    return std::make_shared<IntersectionData>(false);
}
