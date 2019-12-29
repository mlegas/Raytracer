#include "Material.h"

MaterialType Material::GetMaterialType()
{
    return m_materialType;
}

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
