#include <glm/vec3.hpp>
#include <vector>
#include <memory>

enum RayType
{
    shadow, normal
};

class Ray
{
private:
    RayType m_rayType;
    glm::vec3 m_origin;
    glm::vec3 m_direction;
public:
    glm::vec3 getOrigin();
    glm::vec3 getDirection();
    RayType getType();
    Ray(RayType _rayType, glm::vec3 _origin, glm::vec3 _direction);
};

