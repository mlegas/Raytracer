#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object
{
private:
    glm::vec3 m_planeU;
    glm::vec3 m_planeV;
    glm::vec3 m_normal;
    bool m_planeUVsSet;
    glm::vec3 GetTextureColour(std::shared_ptr<IntersectionData> _data);
public:
    Plane(glm::vec3 _position, glm::vec3 _normal);
    std::shared_ptr<IntersectionData> Intersect(std::shared_ptr<Ray> _ray);
};

#endif // PLANE_H
