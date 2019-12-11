#include <glm/ext.hpp>
#include <algorithm>
#include "Ray.h"
#include "Sphere.h"

std::shared_ptr<IntersectionData> Sphere::intersect(std::shared_ptr<Ray> _ray)
{
    if (!m_centerToOriginSet)
    {
        m_mtx.lock();
        m_centerToOrigin = _ray->getOrigin() - m_position;
        m_centerToOriginSquared = glm::dot(m_centerToOrigin, m_centerToOrigin);
        m_centerToOriginSet = true;
        m_mtx.unlock();
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
        return std::make_shared<IntersectionData>(false); // no intersection
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
        return std::make_shared<IntersectionData>(false);
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

    float distance = t;
    glm::vec3 point = _ray->getOrigin() + _ray->getDirection() * t;
    glm::vec3 normal = glm::normalize(point - m_position);
    return std::make_shared<IntersectionData>(true, distance, point, normal);
}

glm::vec3 Sphere::shadePixel(std::shared_ptr<Ray> _ray)
{
   // glm::vec3 v = -(_ray->getDirection());
 //   float facingRatio = std::max(0.0f, glm::dot(v, m_data.m_normal)) * 255.0f;
    return m_albedo;
}

Sphere::Sphere(glm::vec3 _position, float _radius, glm::vec3 _albedo)
{
	m_position = _position;
	m_radius = _radius;
    m_radiusSquared = m_radius * m_radius;
    m_albedo = _albedo;
    m_centerToOriginSet = false;
}
