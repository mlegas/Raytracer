#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object
{
private:
    glm::vec3 m_normal;
public:
    Plane();
    std::shared_ptr<IntersectionData> Intersect(std::shared_ptr<Ray> _ray);
};

#endif // PLANE_H
