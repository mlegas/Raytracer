/** @file Material.h
 *  @brief Base class for materials.
 *
 *  This class provides a few variables and objects that most of the types
 *  of materials have in common, shortcut functions to extract data from
 *  a texture.
 *
 *  It is never supposed to be constructed as an object.
 */

/// The include guards are used as Material.h is used as a base class.
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

/** Texture.h is included here, as some derived classes use textures
 *  and it is easier to just contain it here for linking purposes. */
#include "Texture.h"

/** This enum is used to differentiate between the materials,
 *  as all derived materials used in objects are
 *  pointed to by the use of the base class, Material.
 *  This ensures the use of correct shading functions. */
enum MaterialType
{
    lambertian, metal, dielectric
};

class Material
{
    protected:
        std::shared_ptr<Texture> m_texture;
        bool m_textureSet;
        MaterialType m_materialType;
        glm::vec3 m_colour;

    public:
        /** @brief Returns whether a texture has been set.
         *  Used to determine whether to return a specified colour or extract a colour from a texture. */
        bool IsTextureSet();
        /// @brief Returns the material type.
        MaterialType GetMaterialType();
        /// @brief Returns the stored texture data (colour values for each pixel).
        unsigned char* GetTextureData();
        /// @brief Returns the width of the texture.
        int GetTextureWidth();
        /// @brief Returns the height of the texture.
        int GetTextureHeight();
        /// @brief Returns the colour of the material if specified instead of a texture.
        glm::vec3 GetColour();

        /** The functions below are set as virtual and throw an exception when used by the base class.
         *  They are only set by the derived classes which use them.
         *  This allows for pointing to the derived classes by the use of the base class pointer, Material. */
        /// @brief Returns the albedo value of the material (how much light does it reflect).
        virtual float GetAlbedo();
        /// @brief Returns the reflectivity value of the material (how glossy it is).
        virtual float GetReflectivity();
        /// @brief Returns the refractive index.
        virtual float GetRefractiveIndex();
        /// @brief Returns how transparent is the material.
        virtual float GetTransparency();
};

#endif
