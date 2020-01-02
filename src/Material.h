#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Texture.h"

enum MaterialType
{
    lambertian, metal, dielectric
};

class Material
{

protected:
    std::shared_ptr<Texture> m_texture;
    bool m_textureSet;
    MaterialType m_materialType;
    glm::vec3 m_colour;

public:
    bool IsTextureSet();
    MaterialType GetMaterialType();
    unsigned char* GetTextureData();
    int GetTextureWidth();
    int GetTextureHeight();
    glm::vec3 GetColour();

    virtual float GetAlbedo();
    virtual float GetReflectivity();
    virtual float GetRefractiveIndex();
    virtual float GetTransparency();
};

#endif
