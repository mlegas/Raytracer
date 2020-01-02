#include "Material.h"

class Lambertian : public Material
{
private:
    float m_albedo;
public:
    Lambertian(glm::vec3 _colour, float _albedo);
    Lambertian(std::string _filename, float _albedo);
    float GetAlbedo();
};
