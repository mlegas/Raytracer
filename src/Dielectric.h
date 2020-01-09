#include "Material.h"

class Dielectric : public Material
{
private:
    float m_refractiveIndex;
    float m_transparency;
public:
    Dielectric(glm::vec3 _colour, float _transparency, float _refractiveIndex);
    float GetRefractiveIndex();
    float GetTransparency();
};
