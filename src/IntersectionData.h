/** @file IntersectionData.h
 *  @brief Class for storing the data of a ray-object intersection.
 */

#include <glm/vec3.hpp>

class IntersectionData
{
    private:
        bool m_intersection;
        float m_distance; ///< Stores the distance on the ray's direction to the intersection (t).
        glm::vec3 m_point;
        glm::vec3 m_normal;
    public:
        /** @brief Constructs the intersection data class, used for no intersection.
         *  @param _intersection The validity of the intersection.
         */
        IntersectionData(bool _intersection);
        /** @brief Constructs the intersection data class.
         *  @param _intersection The validity of the intersection.
         *  @param _distance The distance on the ray's direction to the intersection (t).
         *  @param _point The intersection point coordinates.
         *  @param _normal The normal of the intersection point.
         */
        IntersectionData(bool _intersection, float _distance, glm::vec3 _point, glm::vec3 _normal);
        /// @brief Returns whether the intersection happened.
        bool HasIntersected();
        /// @brief Returns the intersection distance on the ray's direction (t).
        float GetIntersectionDistance();
        /// @brief Returns the normal of the intersection point.
        glm::vec3 GetIntersectionNormal();
        /// @brief Returns the intersection point coordinates.
        glm::vec3 GetIntersectionPoint();
};
