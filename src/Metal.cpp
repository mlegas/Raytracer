#include "Metal.h"

Metal::Metal(glm::vec3 _colour, float _albedo, float _reflectivity)
{
    m_colour = _colour;
    m_albedo = _albedo;
    m_reflectivity = _reflectivity;

    m_textureSet = false;
    m_materialType = metal;
}

Metal::Metal(std::string _filename, float _albedo, float _reflectivity)
{
    m_texture = std::make_shared<Texture>(_filename);
    m_albedo = _albedo;
    m_reflectivity = _reflectivity;

    m_textureSet = true;
    m_materialType = metal;
}

float Metal::GetAlbedo()
{
    return m_albedo;
}

float Metal::GetReflectivity()
{
    return m_reflectivity;
}
