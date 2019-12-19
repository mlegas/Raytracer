#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <glm/vec3.hpp>
#include <memory>
#include <vector>

class Object;
class IntersectionData;

class Light
{
protected:
    float m_intensity;
    glm::vec3 m_colour;
public:
    virtual glm::vec3 CalculateLight(std::shared_ptr<IntersectionData> _data, std::shared_ptr<std::vector<std::shared_ptr<Object>>> _objects, float _albedo) = 0;
};

#endif
