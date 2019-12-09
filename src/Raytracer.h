#include <glm/vec3.hpp>
#include <memory>

class Object;
class Ray;
class Scene;

struct Raytracer
{
    glm::vec3 rayTrace(std::shared_ptr<Ray> _ray, std::shared_ptr<Scene> _scene);
    glm::vec3 computeLighting(std::shared_ptr<Scene> _scene, std::shared_ptr<Object> _object);
};

