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
    glm::vec3 rayTrace(std::shared_ptr<Ray> _ray, std::shared_ptr<Scene> _scene);
    glm::vec3 computeLighting(std::shared_ptr<std::vector<std::shared_ptr<Light>>> _lights, std::shared_ptr<IntersectionData> _data);
};

