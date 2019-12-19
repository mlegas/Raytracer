#ifndef _RAY_H_
#define _RAY_H

#include <glm/vec3.hpp>
#include <vector>
#include <memory>

class Ray
{
private:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
public:
    glm::vec3 GetOrigin();
    glm::vec3 GetDirection();
    Ray(glm::vec3 _origin, glm::vec3 _direction);
};

#endif
