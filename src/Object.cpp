#include "Light.h"
#include "Scene.h"
#include "Object.h"

glm::vec3 Object::GetPosition()
{
	return m_position;
}

MaterialType Object::GetMaterialType()
{
    return m_material->GetMaterialType();
}

float Object::GetAlbedo()
{
    return m_material->GetAlbedo();
}

glm::vec3 Object::GetColour()
{
    return m_material->GetColour();
}

float Object::GetReflectivity()
{
    return m_material->GetReflectivity();
}

float Object::GetRefractiveIndex()
{
    return m_material->GetRefractiveIndex();
}

float Object::GetTransparency()
{
    return m_material->GetTransparency();
}
