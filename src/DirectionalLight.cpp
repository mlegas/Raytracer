/** @file DirectionalLight.cpp
 *	@brief Implementation of functions for the DirectionalLight class.
 */

#include "DirectionalLight.h"
#include "Object.h"
#include "Ray.h"
#include <glm/ext.hpp>
#include <algorithm> ///< The algorithm header is needed for the std::max function.

DirectionalLight::DirectionalLight(glm::vec3 _direction, glm::vec3 _colour, float _intensity)
{
    m_direction = glm::normalize(_direction); ///< Normalizes the specified direction in case it has a magnitude over 1.
    m_directionToLight = -m_direction; ///< Sets the direction to the light source for shadow rays.
    m_colour = _colour;
    m_intensity = _intensity;
}

glm::vec3 DirectionalLight::CalculateLight(std::shared_ptr<IntersectionData> _data, std::shared_ptr<std::vector<std::shared_ptr<Object>>> _objects, float _albedo)
{
	float pi = 3.14159265f;

    /** Creates a shadow ray from the intersection point, with a small bias of 0.0001
     *  multiplied by the direction to light to remove the possibility of shadow acne.
     *  Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligth-and-shadows */
    glm::vec3 shadowOrigin = _data->GetIntersectionPoint() + (m_directionToLight * 0.001f);
    glm::vec3 shadowDirection = m_directionToLight; ///< Sets the direction of the shadow ray towards the light source.

    std::shared_ptr<Ray> shadowRay = std::make_shared<Ray>(shadowOrigin, shadowDirection);
    std::shared_ptr<IntersectionData> shadowIntersection;

    std::vector<std::shared_ptr<Object>>::iterator objIterator;

	/** This loop goes through all of the objects and checks whether the shadow ray
	 *  collides with any of the objects on its direction to the light source. */
    for (objIterator = _objects->begin(); objIterator != _objects->end(); objIterator++)
    {
        shadowIntersection = (*objIterator)->Intersect(shadowRay);

        if (shadowIntersection->HasIntersected())
        {
            return glm::vec3(0.0f, 0.0f, 0.0f); ///< Return the background colour (black) on collision, creating a shadow.
        }
    }
	
	/** The std::max ensures that in case the angle between the light source and the intersection point is above 90 degrees,
	 *  there will be no light reflected. A failsafe in case the shadow intersection test failed.
	 *  Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/diffuse-lambertian-shading */
    float lightPower = std::max(0.0f, glm::dot(m_directionToLight, _data->GetIntersectionNormal())) * m_intensity;
    float lightReflected = _albedo / pi; ///< Calculates the amount of reflected light using a derivation of Lambert's cosine law.

    glm::vec3 lightColour = m_colour * lightPower * lightReflected; ///< Returns the amount of light from this light source with its colour.
    return lightColour;
}
