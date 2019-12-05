#include "Object.h"
#include <glm/ext.hpp>
#include <memory>

class Sphere : public Object
{
private:
	float m_radius;
    float m_radiusSquared;
public:
    glm::vec3 shadePixel(std::shared_ptr<Ray> _ray);
    bool intersect(std::shared_ptr<Ray> _ray);
	float getRadius();
    float getRadiusSquared();
    Sphere(glm::vec3 _position, float _radius);
};
