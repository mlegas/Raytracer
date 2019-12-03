#include "Ray.h"
#include "Sphere.h"

bool Sphere::intersect(const Ray &_ray)
{
    glm::vec3 originToCenter = m_position - _ray.m_origin;
    float distanceToCenter = glm::dot(originToCenter, _ray.m_direction);

    if (distanceToCenter < 0.0f)
    {
        return false; // point behind ray
    }

    float distanceSquared = glm::dot(originToCenter, originToCenter) - (distanceToCenter * distanceToCenter);

    if (distanceSquared > m_radiusSquared)
    {
        return false; // no intersection
    }

    float middleToIntersection = sqrt(m_radiusSquared - distanceSquared);

    // solutions for t
    float t0 = distanceToCenter - middleToIntersection;
    float t1 = distanceToCenter + middleToIntersection;

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
    m_data.m_point = _ray.m_origin + _ray.m_direction * t;
    m_data.m_normal = glm::normalize(m_data.m_point - m_position);

    return true;
}

glm::vec3 Sphere::shadePixel(const Ray &_ray)
{
    return glm::vec3(0.0f, 0.0f, 0.0f);
}

float Sphere::getRadius()
{
	return m_radius;
}

float Sphere::getRadiusSquared()
{
    return m_radiusSquared;
}

Sphere::Sphere(glm::vec3 _position, float _radius)
{
	m_position = _position;
	m_radius = _radius;
    m_radiusSquared = m_radius * m_radius;
}
