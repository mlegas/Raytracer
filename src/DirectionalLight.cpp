#include "DirectionalLight.h"
#include "Ray.h"
#include "Object.h"
#include <glm/ext.hpp>

DirectionalLight::DirectionalLight(glm::vec3 _direction, glm::vec3 _colour, float _intensity)
{
    m_direction = glm::normalize(_direction);
    m_directionToLight = -m_direction;
    m_colour = _colour;
    m_intensity = _intensity;
}

glm::vec3 DirectionalLight::CalculateLight(std::shared_ptr<IntersectionData> _data, std::shared_ptr<std::vector<std::shared_ptr<Object>>> _objects, float _albedo)
{
    glm::vec3 shadowOrigin = _data->GetIntersectionPoint() + (m_directionToLight * 0.01f);
    glm::vec3 shadowDirection = m_directionToLight;

    std::shared_ptr<Ray> shadowRay = std::make_shared<Ray>(shadowOrigin, shadowDirection);
    std::shared_ptr<IntersectionData> shadowIntersection;

    std::vector<std::shared_ptr<Object>>::iterator objIterator;

    for (objIterator = _objects->begin(); objIterator != _objects->end(); objIterator++)
    {
        shadowIntersection = (*objIterator)->Intersect(shadowRay);

        if (shadowIntersection->HasIntersected())
        {
            return glm::vec3(0.0f, 0.0f, 0.0f);
        }
    }

    float lightPower = std::max(0.0f, glm::dot(m_directionToLight, _data->GetIntersectionNormal())) * m_intensity;
    float lightReflected = _albedo / M_PI;

    glm::vec3 lightColor = m_colour * lightPower * lightReflected;
    return lightColor;
}
