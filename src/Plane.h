#include "Object.h"

class Plane : public Object
{
private:
    glm::vec3 m_normal;
public:
    Plane(glm::vec3 _position, glm::vec3 _normal, std::shared_ptr<Material> _material);
    std::shared_ptr<IntersectionData> Intersect(std::shared_ptr<Ray> _ray);
};
