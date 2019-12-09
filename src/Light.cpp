#include <glm/ext.hpp>
#include "Light.h"

Light::Light(glm::vec3 _colour, float _intensity)
{
    m_lightType = ambient;
    m_colour = _colour;
    m_intensity = _intensity;
}

Light::Light(glm::vec3 _colour, float _intensity, glm::vec3 _direction)
{
    m_lightType = directional;
    m_colour = _colour;
    m_intensity = _intensity;
    m_direction = glm::normalize(-_direction);
}

Light::Light(glm::vec3 _position, glm::vec3 _colour, float _intensity)
{
    m_lightType = spherical;
    m_position = -_position;
    m_colour = _colour;
    m_intensity = _intensity;
}

LightType Light::getLightType()
{
    return m_lightType;
}

float Light::getLightIntensity()
{
    return m_intensity;
}

glm::vec3 Light::getLightColour()
{
    return m_colour;
}

glm::vec3 Light::getPosition()
{
    return m_position;
}

glm::vec3 Light::getDirection()
{
    return m_direction;
}
