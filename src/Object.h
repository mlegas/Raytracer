/** @file Object.h
 *  @brief Base class for 3D objects.
 *
 *	This class provides a pure virtual function for intersecting to be implemented by
 *  derived classes (types of objects), a virtual function to return a colour value from a texture,
 *  and a few variables that all types of 3D objects have in common.
 *
 *  It is never supposed to be constructed as an object.
 */

/// The include guards are used as Object.h is used as a base class.
#ifndef _OBJECT_H_
#define _OBJECT_H_

/** IntersectionData.h is included here, as some derived classes use it
 *  to extract a pixel colour from a texture using intersection data,
 *  and it is easier to just contain it here for linking purposes. */
#include "IntersectionData.h"
/** Material.h is included here, as all of the derived classes have a material
 *  and it is easier to just contain it here for linking purposes. */
#include "Material.h"
#include <glm/vec3.hpp>
#include <memory>

class Scene;
class Ray;

class Object
{
    protected:
        glm::vec3 m_position; ///< The position of the object.
        std::shared_ptr<Material> m_material; ///< The material of the object.
        /** @brief Extracts pixel colour from a texture, taking into consideration object type.
         *  @param _data The data about the intersection (point, normal, distance [t]).
         */
        virtual glm::vec3 GetTextureColour(std::shared_ptr<IntersectionData> _data);
    public:
        /** @brief Returns whether a given ray intersected with this object, and data about the intersection if true.
         *  @param _ray A ray with origin and direction.
         */
        virtual std::shared_ptr<IntersectionData> Intersect(std::shared_ptr<Ray> _ray) = 0;
        /** @brief Returns a colour value from the object's material, either from a set colour or texture.
         *  @param _data The data about the intersection (point, normal, distance [t]).
         */
        glm::vec3 GetColour(std::shared_ptr<IntersectionData> _data);
        /// @brief Returns position of the object.
        glm::vec3 GetPosition();
        /// @brief Returns the type of the material this object has.
        MaterialType GetMaterialType();
        /// @brief Returns the material this object has.
        std::shared_ptr<Material> GetMaterial();
};

#endif
