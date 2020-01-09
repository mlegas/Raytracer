#include "Dielectric.h"

Dielectric::Dielectric(glm::vec3 _colour, float _transparency, float _refractiveIndex)
{
    m_colour = _colour;
    m_transparency = _transparency;
    m_refractiveIndex = _refractiveIndex;

    m_textureSet = false;
    m_materialType = dielectric;
}

float Dielectric::GetRefractiveIndex()
{
    return m_refractiveIndex;
}

float Dielectric::GetTransparency()
{
    return m_transparency;
}
