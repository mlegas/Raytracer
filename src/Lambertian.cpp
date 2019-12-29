#include "Lambertian.h"

Lambertian::Lambertian(glm::vec3 _colour, float _albedo)
{
    m_colour = _colour;
    m_albedo = _albedo;

    m_textureSet = false;
    m_materialType = lambertian;
}

Lambertian::Lambertian(std::string _filename, float _albedo)
{
    m_texture = std::make_shared<Texture>(_filename);
    m_albedo = _albedo;

    m_textureSet = true;
    m_materialType = lambertian;
}

float Lambertian::GetAlbedo()
{
    return m_albedo;
}
