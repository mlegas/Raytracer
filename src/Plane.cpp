#include "Plane.h"
#include "Ray.h"
#include <glm/ext.hpp>

Plane::Plane(glm::vec3 _position, glm::vec3 _normal)
{
    m_position = _position;
    m_normal = _normal;
}

glm::vec3 Plane::GetTextureColour(std::shared_ptr<IntersectionData> _data)
{
    if (!m_planeUVsSet)
    {
        std::mutex mtx;
        mtx.lock();

        m_planeUVsSet = true;

        glm::vec3 a = glm::cross(m_normal, glm::vec3(1, 0, 0));
        glm::vec3 b = glm::cross(m_normal, glm::vec3(0, 1, 0));

        glm::vec3 max_ab;

        if (glm::dot(a, a) > glm::dot(b, b))
        {
            max_ab = a;
        }

        else
        {
            max_ab = b;
        }

        glm::vec3 c = glm::cross(m_normal, glm::vec3(0, 0, 1));

        if (glm::dot(max_ab, max_ab) > glm::dot(c, c))
        {
            m_planeU = glm::normalize(max_ab);
        }

        else
        {
            m_planeU = glm::normalize(c);
        }

        m_planeV = cross(m_normal, m_planeU);
        mtx.unlock();
    }

    float u = glm::dot(m_planeU, _data->GetIntersectionPoint());
    float v = glm::dot(m_planeV, _data->GetIntersectionPoint());

    unsigned char* data = m_material->GetTextureData();
    int width = m_material->GetTextureWidth();
    int height = m_material->GetTextureHeight();

    int i = u * width;
    int j = (1.0f - v) * height;

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

std::shared_ptr<IntersectionData> Plane::Intersect(std::shared_ptr<Ray> _ray)
{
    float denom = glm::dot(m_normal, _ray->GetDirection());
    float t;

    if (denom > 0.000001f)
    {
        glm::vec3 originToPlane = m_position - _ray->GetOrigin();
        t = glm::dot(originToPlane, m_normal) / denom;

        if (t < 0.0f)
        {
            return std::make_shared<IntersectionData>(false);
        }
    }

    else
    {
        return std::make_shared<IntersectionData>(false);
    }

    float distance = t;
    glm::vec3 point = _ray->GetOrigin() + _ray->GetDirection() * t;
    return std::make_shared<IntersectionData>(true, distance, point, -m_normal);

}
