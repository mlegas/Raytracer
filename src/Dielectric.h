/** @file Dielectric.h
 *  @brief Class for materials with dielectric properties.
 */

#include "Material.h"

class Dielectric : public Material
{
    private:
        float m_refractiveIndex; ///< How much a ray of light bends when passing through the material.
        float m_transparency; ///< How transmissive the material is.
    public:
        /** @brief Constructs a dielectric material.
         *  @param _colour The colour of the material, which all refractions will be affected by.
         *  @param _transparency Sets how transparent the material should be.
         *  @param _refractiveIndex Sets the refractive index.
         */
        Dielectric(glm::vec3 _colour, float _transparency, float _refractiveIndex);
        /// @brief Returns the refractive index.
        float GetRefractiveIndex();
        /// @brief Returns how transparent is the material.
        float GetTransparency();
};
