#include "Object.h"

glm::vec3 Object::getPosition()
{
	return m_position;
}

void Object::setPosition(const glm::vec3 &_position)
{
	m_position = _position;
}

float Object::getIntersectionDistance()
{
    return m_data.m_distance;
}

glm::vec3 Object::getIntersectionNormal()
{
    return m_data.m_normal;
}

glm::vec3 Object::getIntersectionPoint()
{
    return m_data.m_point;
}
