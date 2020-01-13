/** @file Dielectric.cpp
 *  @brief Implementation of functions for the Dielectric class.
 *
 *  As (probably) all existing dielectric materials contain only colour,
 *  there is no need for a textured constructor.
 */

#include "Dielectric.h"

Dielectric::Dielectric(glm::vec3 _colour, float _transparency, float _refractiveIndex)
{
    m_colour = _colour;
    m_transparency = _transparency;
    m_refractiveIndex = _refractiveIndex;

    m_textureSet = false; /**< Ensures that intersection functions will use colour-based functions
                            *  instead of trying to extract the colour from a (non-existing) texture. */
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
