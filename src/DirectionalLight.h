/** @file Dielectric.h
 *  @brief Class for directional lights (such as sun rays).
 */

#include "Light.h"

class DirectionalLight : public Light
{
    private:
        glm::vec3 m_direction;
        glm::vec3 m_directionToLight; ///< The direction to light, as it is the inverted direction of light.
    public:
        /** @brief Constructs a directional light.
         *  @param _direction The direction of the light.
         *  @param _colour The colour of the light.
         *  @param _intensity Sets how intense should the light be.
         */
        DirectionalLight(glm::vec3 _direction, glm::vec3 _colour, float _intensity);
        /** @brief Checks whether the intersection point is visible by the light or in shadow instead.
         *  @param _data The data about the intersection (point, normal, distance [t]).
         *  @param _objects The list of all the objects in the scene.
         *  @param _albedo The albedo value of the intersected object.
         */
        glm::vec3 CalculateLight(std::shared_ptr<IntersectionData> _data, std::shared_ptr<std::vector<std::shared_ptr<Object>>> _objects, float _albedo);
};
