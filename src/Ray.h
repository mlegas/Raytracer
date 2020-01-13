/** @file Ray.h
 *  @brief Class for constructing rays, used in determining intersections with objects.
 */

#include <glm/vec3.hpp>
#include <vector>
#include <memory>

class Ray
{
private:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
public:
	/// @brief Returns the origin of the ray.
    glm::vec3 GetOrigin();
	/// @brief Returns the direction of the ray.
    glm::vec3 GetDirection();
	/** @brief Constructs a ray.
	 *  @param _origin The origin of the ray.
	 *  @param _direction The direction to which the ray is pointing.
	 */
    Ray(glm::vec3 _origin, glm::vec3 _direction);
};
