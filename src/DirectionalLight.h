#include "Light.h"

class DirectionalLight : public Light
{
private:
    glm::vec3 m_direction;
    glm::vec3 m_directionToLight;
public:
    DirectionalLight(glm::vec3 _direction, glm::vec3 _colour, float _intensity);
    glm::vec3 CalculateLight(std::shared_ptr<IntersectionData> _data, std::shared_ptr<std::vector<std::shared_ptr<Object>>> _objects, float _albedo);
};
