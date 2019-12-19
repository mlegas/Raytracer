#include "Material.h"

MaterialType Material::GetMaterialType()
{
    return m_materialType;
}

Material::Material(float _albedo, glm::vec3 _colour)
{
    m_materialType = lambertian;
    m_albedo = _albedo;
    m_colour = _colour;
}

float Material::GetAlbedo()
{
    return m_albedo;
}

glm::vec3 Material::GetColour()
{
    return m_colour;
}
