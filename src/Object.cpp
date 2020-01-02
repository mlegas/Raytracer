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

glm::vec3 Object::GetColour(std::shared_ptr<IntersectionData> _data)
{
    if (m_material->IsTextureSet())
    {
        return GetTextureColour(_data);
    }

    else
    {
        return m_material->GetColour();
    }
}

std::shared_ptr<Material> Object::GetMaterial()
{
    return m_material;
}
