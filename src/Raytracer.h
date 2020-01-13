/** @file Raytracer.h
 *  @brief Raytracer namespace, which contains all necessary functions for shading and raytracing.
 *
 *  Initially implemented as a class, the Raytracer has been moved to a namespace as it does not contain
 *  any variables that could be stored in a multi-threaded environment.
 *
 *  This namespace contains all functions required for shading.
 */

#include <glm/vec3.hpp>
#include <memory>
#include <vector>

class IntersectionData;
class Light;
class Object;
class Ray;
class Scene;

namespace Raytracer
{
    /** @brief Performs diffuse shading taking into consideration material properties, lighting and shadows, and returns a colour.
     *  @param _object The intersected object.
     *  @param _data The data about the intersection (point, normal, distance [t]).
     *  @param _scene Scene containing all of the objects, lights and maximum depth value.
     */
    glm::vec3 CalculateDiffuseColour(std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene);
    /** @brief Calculates the amount of reflected and refracted light in dielectric materials.
     *  @param _ray A ray with origin and direction.
     *  @param _object The intersected object.
     *  @param _scene Scene containing all of the objects, lights and maximum depth value.
     */
    float CalculateFresnel(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data);
    /** @brief Creates a reflection ray from the intersection point, basing on a given ray's direction.
     *  @param _ray A ray with origin and direction.
     *  @param _data The data about the intersection (point, normal, distance [t]).
     */
    std::shared_ptr<Ray> CreateReflectionRay(std::shared_ptr<Ray> _ray, std::shared_ptr<IntersectionData> _data);
    /** @brief Creates a transmission ray for refraction from the intersection point, basing on a ray's direction and the refractive index of an object's material.
     *  @param _ray A ray with origin and direction.
     *  @param _object The intersected object.
     *  @param _data The data about the intersection (point, normal, distance [t]).
     */
    std::shared_ptr<Ray> CreateTransmissionRay(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data);
    /** @brief Checks the given ray for intersection against all objects in the scene, returns the closest intersected object (if any) and shades the point, returning a colour.
     *  @param _ray A ray with origin and direction.
     *  @param _scene Scene containing all of the objects, lights and maximum depth value.
     *  @param _depth The current depth of the ray used recursively in reflecting and refracting.
     */
    glm::vec3 RayTrace(std::shared_ptr<Ray> _ray, std::shared_ptr<Scene> _scene, int _depth);
    /** @brief Shades the current pixel using a ray created by the camera and the material properties of the intersected object (if any), returning a colour.
     *  @param _ray A ray with origin and direction.
     *  @param _object The intersected object.
     *  @param _data The data about the intersection (point, normal, distance [t]).
     *  @param _scene Scene containing all of the objects, lights and maximum depth value.
     *  @param _depth The current depth of the ray used recursively in reflecting and refracting.
     */
    glm::vec3 ShadePixel(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene, unsigned int _depth);
};
