#include <glm/vec3.hpp>
#include <vector>
#include <memory>

class IntersectionData;
class Light;
class Object;
class Ray;
class Scene;

namespace Raytracer
{
    glm::vec3 RayTrace(std::shared_ptr<Ray> _ray, std::shared_ptr<Scene> _scene, unsigned int _depth);
    std::shared_ptr<Ray> CreateReflectionRay(std::shared_ptr<Ray> _ray, std::shared_ptr<IntersectionData> _data);
    std::shared_ptr<Ray> CreateTransmissionRay(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data);
    glm::vec3 CalculateDiffuseColour(std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene);
    float CalculateFresnel(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data);
    glm::vec3 ShadePixel(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene, unsigned int _depth);
};
