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
    float denom = glm::dot(m_normal, _ray->GetDirection());
    float t;

    if (denom > 0.000001f)
    {
        glm::vec3 originToPlane = m_position - _ray->GetOrigin();
        t = glm::dot(originToPlane, m_normal) / denom;

        if (t >= 0.0f)
        {
            float distance = t;
            glm::vec3 point = _ray->GetOrigin() + _ray->GetDirection() * t;
            return std::make_shared<IntersectionData>(true, distance, point, -m_normal);
        }
    }

    return std::make_shared<IntersectionData>(false);
}
