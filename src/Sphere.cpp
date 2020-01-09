#include <glm/ext.hpp>
#include <algorithm>
#include <iostream>
#include "Ray.h"
#include "Sphere.h"

std::shared_ptr<IntersectionData> Sphere::Intersect(std::shared_ptr<Ray> _ray)
{
    glm::vec3 centerToOrigin = _ray->GetOrigin() - m_position;
    float centerToOriginSquared = glm::dot(centerToOrigin, centerToOrigin);

    float a = glm::dot(_ray->GetDirection(), _ray->GetDirection());
    float b = 2.0f * glm::dot(_ray->GetDirection(), centerToOrigin);
    float c = centerToOriginSquared - m_radiusSquared;

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
    glm::vec3 point = _ray->GetOrigin() + _ray->GetDirection() * t;
    glm::vec3 normal = glm::normalize(point - m_position);
    return std::make_shared<IntersectionData>(true, distance, point, normal);
}

glm::vec3 Sphere::GetTextureColour(std::shared_ptr<IntersectionData> _data)
{
	float pi = 3.14159265f;

    float phi = std::atan2(_data->GetIntersectionNormal().x, _data->GetIntersectionNormal().z);
    float theta = glm::asin(_data->GetIntersectionNormal().y);
    float u = (phi + pi) / (2.0f * pi);
    float v = (theta + pi / 2.0f) / pi;

    unsigned char* data = m_material->GetTextureData();
    int width = m_material->GetTextureWidth();
    int height = m_material->GetTextureHeight();

    int i = u * width;
    int j = (1.0f - v) * height - 0.001f;

    if (i < 0)
    {
        i = 0;
    }

    else if (i > width - 1)
    {
        i = width - 1;
    }

    if (j < 0)
    {
        j = 0;
    }

    else if (j > height - 1)
    {
        j = height - 1;
    }

    float r = data[3 * i + 3 * width * j] / 255.0f;
    float g = data[3 * i + 3 * width * j + 1] / 255.0f;
    float b = data[3 * i + 3 * width * j + 2] / 255.0f;

    return glm::vec3(r, g, b);
}

Sphere::Sphere(glm::vec3 _position, float _radius, std::shared_ptr<Material> _material)
{
	m_position = _position;
	m_radius = _radius;
    m_radiusSquared = m_radius * m_radius;
    m_material = _material;
}
