#include "SphericalLight.h"
#include "Ray.h"
#include "Object.h"
#include <glm/ext.hpp>
#include <algorithm>

SphericalLight::SphericalLight(glm::vec3 _position, glm::vec3 _colour, float _intensity)
{
    m_position = _position;
    m_colour = _colour;
    m_intensity = _intensity;
}

glm::vec3 SphericalLight::CalculateLight(std::shared_ptr<IntersectionData> _data, std::shared_ptr<std::vector<std::shared_ptr<Object>>> _objects, float _albedo)
{
	float pi = 3.14159265f;

    glm::vec3 directionToLight = m_position - _data->GetIntersectionPoint();
    float distanceSquared = glm::dot(directionToLight, directionToLight);
    directionToLight = glm::normalize(directionToLight);

    glm::vec3 shadowOrigin = _data->GetIntersectionPoint() + (directionToLight * 0.01f);
    glm::vec3 shadowDirection = directionToLight;

    float distanceToLight = glm::length(m_position - _data->GetIntersectionPoint());

    float lightIntensity = m_intensity / (4.0f * pi * distanceSquared);

    std::shared_ptr<Ray> shadowRay = std::make_shared<Ray>(shadowOrigin, shadowDirection);
    std::shared_ptr<IntersectionData> shadowIntersection;

    std::vector<std::shared_ptr<Object>>::iterator objIterator;

    for (objIterator = _objects->begin(); objIterator != _objects->end(); objIterator++)
    {
        shadowIntersection = (*objIterator)->Intersect(shadowRay);

        if (shadowIntersection->HasIntersected())
        {
            if (glm::length(shadowIntersection->GetIntersectionPoint() - _data->GetIntersectionPoint()) <= distanceToLight)
            {
                return glm::vec3(0.0f, 0.0f, 0.0f);
            }
        }
    }

    float lightPower = std::max(0.0f, glm::dot(directionToLight, _data->GetIntersectionNormal())) * m_intensity;
    float lightReflected = _albedo / pi;

    glm::vec3 lightColor = m_colour * lightPower * lightReflected;
    return lightColor;
}
