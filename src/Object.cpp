/** @file Object.cpp
 *  @brief Implementation of functions for the Object class.
 */

#include "Object.h"
#include <exception>

glm::vec3 Object::GetPosition()
{
    return m_position;
}

/// This function is a shortcut to the Material object.
MaterialType Object::GetMaterialType()
{
    return m_material->GetMaterialType();
}

glm::vec3 Object::GetColour(std::shared_ptr<IntersectionData> _data)
{
    /** If a material has a set and loaded texture, extract the pixel colour from it,
     *  depending on where the ray intersected the object. */
    if (m_material->IsTextureSet())
    {
        return GetTextureColour(_data);
    }

    /// Returns a specified colour otherwise.
    else
    {
        return m_material->GetColour();
    }
}

std::shared_ptr<Material> Object::GetMaterial()
{
    return m_material;
}

/** Although this function below could be empty, it is set to throw
 *  an exception. This is due to the fact that the direct usage of them
 *  means that the Object class has been constructed as an object,
 *  which will inevitably break the raytracing process as this function
 *  should not and do not return anything when used in the base class.
 *
 *  The function could be set to return a background (black) colour instead
 *  with a debugging log in the terminal, but this would most likely
 *  end in a difficult debugging process in hindsight. */
glm::vec3 Object::GetTextureColour(std::shared_ptr<IntersectionData> _data)
{
    throw "The raytracer used base class Object functions.\n";
}
