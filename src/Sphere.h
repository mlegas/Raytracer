#include "Object.h"
#include <glm/ext.hpp>
#include <memory>

class Sphere : public Object
{
private:
	float m_radius;
    float m_radiusSquared;
public:
    glm::vec3 shadePixel(const Ray &_ray);
    bool intersect(const Ray &_ray);
	float getRadius();
    float getRadiusSquared();
    Sphere(glm::vec3 _position, float _radius);
};
