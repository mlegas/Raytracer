#include <glm/ext.hpp>
#include <vector>
#include <memory>

struct Ray
{
    glm::vec3 m_origin;
    glm::vec3 m_direction;
    Ray(glm::vec3 _origin, glm::vec3 _direction);
};

