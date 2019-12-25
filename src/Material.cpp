#include "Material.h"

MaterialType Material::GetMaterialType()
{
    return m_materialType;
}

Material::Material(float _albedo, glm::vec3 _colour)
{
    m_materialType = metal;
    m_albedo = _albedo;
    m_colour = _colour;
    m_reflectivity = 0.001f;
}

float Material::GetAlbedo()
{
    return m_albedo;
}

glm::vec3 Material::GetColour()
{
    return m_colour;
}

float Material::GetReflectivity()
{
    return m_reflectivity;
}

float Material::GetRefractiveIndex()
{
    return m_refractiveIndex;
}

float Material::GetTransparency()
{
    return m_transparency;
}
