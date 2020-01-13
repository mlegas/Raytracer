/** @file SphericalLight.h
 *  @brief Class for spherical lights, such as light bulbs.
 */

#include "Light.h"

class SphericalLight : public Light
{
private:
    glm::vec3 m_position; ///< The position of the light.
public:
    /** @brief Constructs a spherical light.
     *  @param _position The position of the light.
     *  @param _colour The colour of the light.
     *  @param _intensity Sets how intense should the light be.
     */
    SphericalLight(glm::vec3 _position, glm::vec3 _colour, float _intensity);
    /** @brief Checks whether the intersection point is visible by the light or in shadow instead.
     *  @param _data The data about the intersection (point, normal, distance [t]).
     *  @param _objects The list of all the objects in the scene.
     *  @param _albedo The albedo value of the intersected object.
     */
    glm::vec3 CalculateLight(std::shared_ptr<IntersectionData> _data, std::shared_ptr<std::vector<std::shared_ptr<Object>>> _objects, float _albedo);
};
