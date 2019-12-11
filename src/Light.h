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
    float m_intensity;
    LightType m_lightType;
    glm::vec3 m_colour;
    glm::vec3 m_light;
public:
    Light(glm::vec3 _colour, float _intensity);
    Light(glm::vec3 _colour, float _intensity, glm::vec3 _direction);
    Light(glm::vec3 _colour, glm::vec3 _position, float _intensity);
    LightType getLightType();
    glm::vec3 getLight();
    glm::vec3 getPosition();
    glm::vec3 getDirection();
};
