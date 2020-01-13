/** @file Metal.h
 *  @brief Class for materials with metal properties.
 */

#include "Material.h"

class Metal : public Material
{
    private:
        float m_albedo; ///< The albedo value of the material (how much light does it reflect).
        float m_reflectivity; ///< How much light does the material reflect (a low value will return more of the material's own colour).
    public:
        /** @brief Constructs a coloured metal material.
         *  @param _colour The colour of the material.
         *  @param _albedo Sets how much light will the material reflect.
         *  @param _reflectivity Sets how reflective the material will be.
         */
        Metal(glm::vec3 _colour, float _albedo, float _reflectivity);
        /** @brief Constructs a textured metal material.
         *  @param _filename The path to the texture.
         *  @param _reflectivity Sets how reflective the material will be.
         */
        Metal(std::string _filename, float _albedo, float _reflectivity);
        /// @brief Returns the albedo value of the material (how much light does it reflect).
        float GetAlbedo();
        /// @brief Returns the reflectivity value of the material (how glossy it is).
        float GetReflectivity();
};
