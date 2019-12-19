#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include <glm/vec3.hpp>
#include <vector>
#include <memory>

class IntersectionData;
class Light;
class Object;
class Ray;
class Scene;

struct Raytracer
{
    glm::vec3 RayTrace(std::shared_ptr<Ray> _ray, std::shared_ptr<Scene> _scene);
    glm::vec3 ComputeLighting(std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene);
    glm::vec3 Reflect(std::shared_ptr<Ray> _ray, std::shared_ptr<IntersectionData> _data);
};

#endif
