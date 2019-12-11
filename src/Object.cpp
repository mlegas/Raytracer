#include "Object.h"

glm::vec3 Object::getPosition()
{
	return m_position;
}

void Object::setPosition(const glm::vec3 &_position)
{
	m_position = _position;
}

glm::vec3 Object::getAlbedo()
{
    return m_albedo;
}
