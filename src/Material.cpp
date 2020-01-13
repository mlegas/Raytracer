/** @file Material.cpp
 *  @brief Implementation of functions for the Material class.
 */

#include "Material.h"
#include <exception>

MaterialType Material::GetMaterialType()
{
    return m_materialType;
}

/// These three functions are shortcuts to the Texture object.
int Material::GetTextureWidth()
{
    return m_texture->GetWidth();
}

int Material::GetTextureHeight()
{
    return m_texture->GetHeight();
}

unsigned char* Material::GetTextureData()
{
    return m_texture->GetData();
}

glm::vec3 Material::GetColour()
{
    return m_colour;
}

bool Material::IsTextureSet()
{
    return m_textureSet;
}

/** Although the functions below could be empty, they are set to throw
 *  exceptions. This is due to the fact that the direct usage of them
 *  means that the Material class has been constructed as an object,
 *  which will inevitably break the raytracing process as these functions
 *  should not and do not return anything when used in the base class.
 *
 *  They could be set to return a background (black) colour instead,
 *  but this would most likely end in a difficult debugging process
 *  in hindsight. */
float Material::GetAlbedo()
{
    throw "The raytracer used base class Material functions.\n";
}

float Material::GetReflectivity()
{
    throw "The raytracer used base class Material functions.\n";
}

float Material::GetRefractiveIndex()
{
    throw "The raytracer used base class Material functions.\n";
}

float Material::GetTransparency()
{
    throw "The raytracer used base class Material functions.\n";
}
