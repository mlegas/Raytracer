#include <glm/vec3.hpp>

enum LightType
{
    ambient, directional, spherical
};

class Light
{
private:
    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_colour;
    glm::vec3 m_light;
    float m_intensity;
    LightType m_lightType;
public:
    Light(glm::vec3 _colour, float _intensity);
    Light(glm::vec3 _colour, float _intensity, glm::vec3 _direction);
    Light(glm::vec3 _position, glm::vec3 _colour, float _intensity);
    LightType getLightType();
    glm::vec3 getLight();
    glm::vec3 getPosition();
    glm::vec3 getDirection();
};
