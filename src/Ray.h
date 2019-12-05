#include <glm/ext.hpp>
#include <vector>
#include <memory>

class Ray
{
private:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
public:
    glm::vec3 getOrigin();
    glm::vec3 getDirection();
    Ray(glm::vec3 _origin, glm::vec3 _direction);
};

