/** @file Dielectric.cpp
 *  @brief Implementation of functions for the Lambertian class.
 */

#include "Lambertian.h"

Lambertian::Lambertian(glm::vec3 _colour, float _albedo)
{
    m_colour = _colour;
    m_albedo = _albedo;

    m_textureSet = false; /**< Ensures that intersection functions will use colour-based functions
                           *  instead of trying to extract the colour from a (non-existing) texture. */
    m_materialType = lambertian;
}

Lambertian::Lambertian(std::string _filename, float _albedo)
{
    m_texture = std::make_shared<Texture>(_filename); ///< Loads a texture from the specified file path.
    m_albedo = _albedo;

    m_textureSet = true; /**< Ensures that intersection functions will use texture-based functions
                          *  instead of trying to return a (non-existing) colour value from the material. */
    m_materialType = lambertian;
}

float Lambertian::GetAlbedo()
{
    return m_albedo;
}
