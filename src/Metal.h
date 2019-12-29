#ifndef METAL_H
#define METAL_H

#include "Material.h"

class Metal : public Material
{
private:
    float m_albedo;
    float m_reflectivity;
public:
    Metal(glm::vec3 _colour, float _albedo, float _reflectivity);
    Metal(std::string _filename, float _albedo, float _reflectivity);
    float GetAlbedo();
    float GetReflectivity();
};

#endif // METAL_H
