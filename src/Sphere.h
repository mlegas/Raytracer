/** @file Sphere.h
 *  @brief Class for 3D spheres.
 */

#include "Object.h"
#include <glm/vec3.hpp>
#include <mutex>
#include <memory>

class Sphere : public Object
{
    private:
        float m_radius; ///< Radius of the sphere.
        float m_radiusSquared; ///< Stores the squared radius for intersection calculations.
        /** @brief Extracts pixel colour from a texture, if it is set.
         *  @param _data The data about the intersection (point, normal, distance [t]).
         */
        glm::vec3 GetTextureColour(std::shared_ptr<IntersectionData> _data);
    public:
        /** @brief Returns whether a given ray intersected with this sphere, and data about the intersection if true.
         *  Uses the analytic solution for determining an intersection.
         *  @param _ray A ray with origin and direction.
         */
        std::shared_ptr<IntersectionData> Intersect(std::shared_ptr<Ray> _ray);
        /** @brief Constructs a sphere.
         *  @param _position The position of the sphere.
         *  @param _radius The radius of the sphere.
         *  @param _material The material which this sphere will use.
         */
        Sphere(glm::vec3 _position, float _radius, std::shared_ptr<Material> _material);
};
