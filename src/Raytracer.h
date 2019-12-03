#include <glm/ext.hpp>
#include <memory>

class Ray;
class Scene;

class Raytracer
{
public:
    glm::vec3 RayTrace(const Ray &_ray, std::shared_ptr<Scene> _scene);
};

