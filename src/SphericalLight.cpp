/** @file SphericalLight.cpp
 *	@brief Implementation of functions for the SphericalLight class.
 */

#include "SphericalLight.h"
#include "Object.h"
#include "Ray.h"
#include <glm/ext.hpp>
#include <algorithm>

SphericalLight::SphericalLight(glm::vec3 _position, glm::vec3 _colour, float _intensity)
{
    m_position = _position;
    m_colour = _colour;
    m_intensity = _intensity;
}

glm::vec3 SphericalLight::CalculateLight(std::shared_ptr<IntersectionData> _data, std::shared_ptr<std::vector<std::shared_ptr<Object>>> _objects, float _albedo)
{
	float pi = 3.14159265f;

    /// Sets the initial direction vector to the vector from the intersection point to the light.
    glm::vec3 directionToLight = m_position - _data->GetIntersectionPoint();

    /// Dot product of a vector with itself results in a square of its magnitude.
    float distanceSquared = glm::dot(directionToLight, directionToLight);
    /// Normalizes the direction to use as the shadow ray's direction.
    directionToLight = glm::normalize(directionToLight);

    /** Creates a shadow ray from the intersection point, with a small bias of 0.0001
     *  multiplied by the direction to light to remove the possibility of shadow acne. */
    glm::vec3 shadowOrigin = _data->GetIntersectionPoint() + (directionToLight * 0.001f);
    glm::vec3 shadowDirection = directionToLight;

    /** Calculates the magnitude of the vector from the intersection point to the light.
     *  glm::length() could be used here, although since we have already calculated the squared distance
     *  we can just square root it to receive the distance. */
    float distanceToLight = glm::sqrt(distanceSquared);

    /** Applies square falloff to the light to realistically simulate a spherical light shadow.
     *  Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-spherical-light */
    float lightIntensity = m_intensity / (4.0f * pi * distanceSquared);

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
            /// Check if the shadow ray has passed the light source returned before intersecting.
            if (glm::length(shadowIntersection->GetIntersectionPoint() - _data->GetIntersectionPoint()) <= distanceToLight)
            {
                /// The ray intersected on its way to the light source, return background colour.
                return glm::vec3(0.0f, 0.0f, 0.0f);
            }
        }
    }

    /** The std::max ensures that in case the angle between the light source and the intersection point is above 90 degrees,
     *  there will be no light reflected. A failsafe in case the shadow intersection test failed.
     *  Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/diffuse-lambertian-shading */
    float lightPower = std::max(0.0f, glm::dot(directionToLight, _data->GetIntersectionNormal())) * lightIntensity;
    float lightReflected = _albedo / pi; ///< Calculates the amount of reflected light using a derivation of Lambert's cosine law.

    glm::vec3 lightColor = m_colour * lightPower * lightReflected; ///< Returns the amount of light from this light source with its colour.
    return lightColor;
}
