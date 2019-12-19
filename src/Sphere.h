#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Object.h"
#include <glm/vec3.hpp>
#include <mutex>
#include <memory>

class Sphere : public Object
{
private:
	float m_radius;
    float m_radiusSquared;
public:
    std::shared_ptr<IntersectionData> Intersect(std::shared_ptr<Ray> _ray);
    Sphere(glm::vec3 _position, float _radius, std::shared_ptr<Material> _material);
};

#endif
