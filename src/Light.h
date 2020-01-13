/** @file Light.h
 *  @brief Base class for lights.
 *
 *  This class provides a pure virtual function to be implemented by
 *  derived classes (types of light) and a few variables that all types
 *  of light have in common.
 *
 *  It is never supposed to be constructed as an object.
 */

/// The include guards are used as Light.h is used as a base class.
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <glm/vec3.hpp>
#include <memory>
#include <vector>

class Object;
class IntersectionData;

class Light
{
    protected:
        float m_intensity; ///< How intense the light is.
        glm::vec3 m_colour; ///< The colour of the light.
    public:
        /** @brief Checks whether the intersection point is visible by the light or in shadow instead, and calculates the visible colour.
         *  @param _data The data about the intersection (point, normal, distance [t]).
         *  @param _objects The list of all the objects in the scene.
         *  @param _albedo The albedo value of the intersected object.
         */
        virtual glm::vec3 CalculateLight(std::shared_ptr<IntersectionData> _data, std::shared_ptr<std::vector<std::shared_ptr<Object>>> _objects, float _albedo) = 0;
};

#endif
