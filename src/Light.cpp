#include <glm/ext.hpp>
#include "Light.h"

Light::Light(glm::vec3 _colour, float _intensity)
{
    m_lightType = ambient;
    m_colour = _colour / 255.0f;
    m_intensity = _intensity;
    m_light = m_intensity * m_colour;
}

Light::Light(glm::vec3 _colour, float _intensity, glm::vec3 _direction)
{
    m_lightType = directional;
    m_colour = _colour / 255.0f;
    m_intensity = _intensity;
    m_direction = glm::normalize(_direction);
    m_light = m_intensity * m_colour;
}

Light::Light(glm::vec3 _position, glm::vec3 _colour, float _intensity)
{
    m_lightType = spherical;
    m_position = _position;
    m_colour = _colour / 255.0f;
    m_intensity = _intensity;
    m_light = m_intensity * m_colour;
}

LightType Light::getLightType()
{
    return m_lightType;
}

glm::vec3 Light::getLight()
{
    return m_light;
}

glm::vec3 Light::getPosition()
{
    return m_position;
}

glm::vec3 Light::getDirection()
{
    return m_direction;
}
