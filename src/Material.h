#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Texture.h"

enum MaterialType
{
    lambertian, metal, dielectric
};

class Texture;

class Material
{
private:
   // Texture m_texture;
    MaterialType m_materialType;
    float m_reflectivity;
    float m_transparency;
    float m_albedo;
    glm::vec3 m_colour;

public:
    Material(float _albedo, glm::vec3 _colour);
    Material(std::string _filename, MaterialType _materialType, float _fuzz);
    MaterialType GetMaterialType();
//    glm::vec3 getTextureValue(std::shared_ptr<Sphere> _sphere);
//    glm::vec3 getTextureValue(std::shared_ptr<Plane> _plane);
    float GetAlbedo();
    glm::vec3 GetColour();
};

#endif
