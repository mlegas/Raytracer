#ifndef _SPHERICALLIGHT_H_
#define _SPHERICALLIGHT_H_

#include "Light.h"

class SphericalLight : public Light
{
private:
    glm::vec3 m_position;
public:
    SphericalLight(glm::vec3 _position, glm::vec3 _colour, float _intensity);
    glm::vec3 CalculateLight(std::shared_ptr<IntersectionData> _data, std::shared_ptr<std::vector<std::shared_ptr<Object>>> _objects, float _albedo);
};

#endif
