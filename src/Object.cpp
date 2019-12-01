#include "Object.h"

glm::vec3 Object::getPosition()
{
	return m_position;
}

void Object::setPosition(glm::vec3 _position)
{
	m_position = _position;
}