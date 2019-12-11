#include <glm/vec3.hpp>

class IntersectionData
{
private:
    bool m_intersection;
    float m_distance;
    glm::vec3 m_point;
    glm::vec3 m_normal;
public:
    IntersectionData(bool _intersection);
    IntersectionData(bool _intersection, float _distance, glm::vec3 _point, glm::vec3 _normal);
    bool hasIntersected();
    float getIntersectionDistance();
    glm::vec3 getIntersectionNormal();
    glm::vec3 getIntersectionPoint();
};
