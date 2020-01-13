/** @file Plane.h
 *  @brief Class for 3D planes.
 *
 *  @todo Implement GetTextureColour() for planes.
 */

#include "Object.h"

class Plane : public Object
{
    private:
        glm::vec3 m_normal; ///< The normal of the plane, which allows to rotate the plane.
    public:
        /** @brief Constructs a plane.
         *  @param _position The position of the plane.
         *  @param _albedo The normal of the plane (which way is its behind wall pointing to).
         *  @param _material The material which this plane will use.
         */
        Plane(glm::vec3 _position, glm::vec3 _normal, std::shared_ptr<Material> _material);
        /** @brief Returns whether a given ray intersected with this plane, and data about the intersection if true.
         *  @param _ray A ray with origin and direction.
         */
        std::shared_ptr<IntersectionData> Intersect(std::shared_ptr<Ray> _ray);
};
