/** @file Dielectric.h
 *  @brief Class for materials with lambertian properties.
 */

#include "Material.h"

class Lambertian : public Material
{
    private:
        float m_albedo; ///< The albedo value of the material (how much light does it reflect).
    public:
        /** @brief Constructs a coloured lambertian material.
         *  @param _colour The colour of the material.
         *  @param _albedo Sets how much light will the material reflect.
         */
        Lambertian(glm::vec3 _colour, float _albedo);
        /** @brief Constructs a textured lambertian material.
         *  @param _filename The path to the texture.
         *  @param _albedo Sets how much light will the material reflect.
         */
        Lambertian(std::string _filename, float _albedo);
        /// @brief Returns the albedo value of the material (how much light does it reflect).
        float GetAlbedo();
};
