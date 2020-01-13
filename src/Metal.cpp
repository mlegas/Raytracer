/** @file Metal.cpp
 *	@brief Implementation of functions for the Metal class. 
 */

#include "Metal.h"

Metal::Metal(glm::vec3 _colour, float _albedo, float _reflectivity)
{
    m_colour = _colour;
    m_albedo = _albedo;
    m_reflectivity = _reflectivity;

    m_textureSet = false; /**< Ensures that intersection functions will use colour-based functions 
						   *  instead of trying to extract the colour from a (non-existing) texture. */ 
    m_materialType = metal;
}

Metal::Metal(std::string _filename, float _albedo, float _reflectivity)
{
    m_texture = std::make_shared<Texture>(_filename); ///< Loads a texture from the specified file path.
    m_albedo = _albedo;
    m_reflectivity = _reflectivity;

    m_textureSet = true; /**< Ensures that intersection functions will use texture-based functions 
						  *  instead of trying to return a (non-existing) colour value from the material. */ 
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
