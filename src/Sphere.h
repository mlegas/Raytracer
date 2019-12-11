#include "Object.h"
#include <glm/vec3.hpp>
#include <mutex>
#include <memory>

class Sphere : public Object
{
private:
    std::mutex m_mtx;
	float m_radius;
    float m_radiusSquared;
    glm::vec3 m_centerToOrigin;
    float m_centerToOriginSquared;
    bool m_centerToOriginSet;
public:
    glm::vec3 shadePixel(std::shared_ptr<Ray> _ray);
    std::shared_ptr<IntersectionData> intersect(std::shared_ptr<Ray> _ray);
    Sphere(glm::vec3 _position, float _radius, glm::vec3 _albedo);
};
