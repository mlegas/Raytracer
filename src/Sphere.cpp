#include <glm/ext.hpp>
#include <algorithm>
#include "Ray.h"
#include "Sphere.h"

bool Sphere::intersect(std::shared_ptr<Ray> _ray)
{
    if (!m_centerToOriginSet)
    {
        m_centerToOrigin = _ray->getOrigin() - m_position;
        m_centerToOriginSquared = glm::dot(m_centerToOrigin, m_centerToOrigin);
        m_centerToOriginSet = true;
    }

    float a = glm::dot(_ray->getDirection(), _ray->getDirection());
    float b = 2.0f * glm::dot(_ray->getDirection(), m_centerToOrigin);
    float c = m_centerToOriginSquared - m_radiusSquared;

    float discriminant = (b * b) - (4 * a * c);

    // solutions for t
    float t0;
    float t1;

    if (discriminant < 0.0f)
    {
        return false; // no intersection
    }

    else if (discriminant < std::numeric_limits<float>::epsilon())
    {
        t0 = t1 = - 0.5f * b / a;
    }

    else
    {
        float q;

        if (b > 0.0f)
        {
            q = -0.5f * (b + sqrt(discriminant));
        }

        else
        {
            q = -0.5f * (b - sqrt(discriminant));
        }

        t0 = q / a;
        t1 = c / q;
     }

    float t;

    if (t0 < 0 && t1 < 0)
    {
        return false;
    }

    else if (t0 < 0 && t1 >= 0)
    {
        t = t1;
    }

    else if (t0 >= 0 && t1 < 0)
    {
        t = t0;
    }

    else
    {
        if (t0 < t1)
        {
            t = t0;
        }

        else
        {
            t = t1;
        }
    }

    m_data.m_distance = t;
    m_data.m_point = _ray->getOrigin() + _ray->getDirection() * t;
    m_data.m_normal = glm::normalize(m_data.m_point - m_position);

    return true;
}

glm::vec3 Sphere::shadePixel(std::shared_ptr<Ray> _ray)
{
    glm::vec3 v = -(_ray->getDirection());
    float facingRatio = std::max(0.0f, glm::dot(v, m_data.m_normal)) * 255.0f;
    return glm::vec3(facingRatio, facingRatio, facingRatio);
}

Sphere::Sphere(glm::vec3 _position, float _radius)
{
	m_position = _position;
	m_radius = _radius;
    m_radiusSquared = m_radius * m_radius;
    m_centerToOriginSet = false;
}
