/** @file Raytracer.cpp
 *	@brief Implementation of raytracing functions for the Raytracer namespace.
 *
 *  All of the colour calculations in these functions are in the range between 0 and 1.
 *  The colours are converted to a range between 0 and 255 just before returning the colour to the renderer
 *  in the last steps of the RayTrace function.
 *
 *  Many of these functions have been written with great help from Scratchapixel and Brook Heisler's page.
 */

#include "Raytracer.h"
#include "Dielectric.h"
#include "Lambertian.h"
#include "Light.h"
#include "Metal.h"
#include "Object.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include <glm/ext.hpp>
#include <algorithm> ///< The algorithm header is needed for the std::max function.
#include <cfloat> ///< The cfloat header is needed for the FLT_MAX value.
#include <iostream>

glm::vec3 Raytracer::CalculateDiffuseColour(std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene)
{
    std::vector<std::shared_ptr<Light>>::iterator lightIterator;
    glm::vec3 totalLight(0.0f);

	/// Loop through all lights in the scene.
    for (lightIterator = _scene->GetLights()->begin(); lightIterator != _scene->GetLights()->end(); lightIterator++)
    {
		/** This line calculates and sums up all light the given object receives, so that
		 *  in case one light casts a shadow on the object and another is casting light directly onto it,
		 *  it will still be visible.
		 *
		 *  Each derived Light class contains its own function to handle the lighting calculations. 
		 *  The Scene object is passed to provide the objects vector to check for possible shadows. */
        totalLight = totalLight + _object->GetColour(_data) * (*lightIterator)->CalculateLight(_data, _scene->GetObjects(), _object->GetMaterial()->GetAlbedo());
    }

    return totalLight; ///< Returns the total light this object receives.
}

float Raytracer::CalculateFresnel(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data)
{
    /// Reference for the Fresnel formulas: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel

    /// Calculate the cosine of the angle of the incident.
    float cosIncident = glm::dot(_ray->GetDirection(), _data->GetIntersectionNormal());
    /// Set the refractive index of the ray intersecting the object (1.0f as approximation for air).
    float etaIncident = 1.0f;
    /// Set the refractive index of the intersected material as the transmission refractive index.
    float etaTransmission = _object->GetMaterial()->GetRefractiveIndex();

    if (cosIncident > 0.0f)
    {
        /** The incident ray has hit the object from its inside.
         *
         *  We need to swap the incides of refraction, as in case of refraction, the ray will be leaving the
         *  object (we approximate the refractive index of air to be 1.0f). */
        etaIncident = etaTransmission;
        etaTransmission = 1.0f;
    }

    /** Check whether the angle of incident is higher than the "critical angle."
     *  Since we are not calcutaing the direction of the transmission ray and therefore
     *  cannot compare a term of the refraction equation to speed up the calculations,
     *  we need to calculate the sine of the angle of refraction using Snell's law.*/
    float sinTransmission = etaIncident / etaTransmission * glm::sqrt(std::max((1.0f - cosIncident * cosIncident), 0.0f));

    if (sinTransmission > 1.0f)
    {
        /** The sine of the angle of refraction is above 1, meaning that
         *  the total internal reflection is above the "critical angle" (Snell's law).
         *  Return 1.0f (reflection ratio). */
        return 1.0f;
    }

    else
    {
        /// Calculate the cosine of the angle of refraction using the Pythagorean trigonometric identity.
        float cosTransmission = glm::sqrt(std::max((1.0f - sinTransmission * sinTransmission), 0.0f));
        /** We need the cosine of the angle of the incident to be above 0
         *  for the returned reflection ratio to be above 0 as well. */
        float cosIncident = glm::abs(cosTransmission);
        /// Calculate the reflection coefficient for perpendicularly polarized light (s-polarized light).
        float rs = ((etaTransmission * cosIncident) - (etaIncident * cosTransmission)) /
                ((etaTransmission * cosIncident) + (etaIncident * cosTransmission));     
        /// Calculate the reflection coefficient for parallelly polarized light (p-polarized light).
        float rp = ((etaIncident * cosIncident) - (etaTransmission * cosTransmission)) /
                ((etaIncident * cosIncident) + (etaTransmission * cosTransmission));

        /// Calculate the average of both to receive the reflection ratio.
        return (rs * rs + rp * rp) / 2.0f;
    }
}

std::shared_ptr<Ray> Raytracer::CreateReflectionRay(std::shared_ptr<Ray> _ray, std::shared_ptr<IntersectionData> _data)
{
    /** Reference for the direction of the reflection: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
     *  A small bias is added to the origin from the intersection point to ensure that the ray's origin is not inside the object. */
    glm::vec3 reflectOrigin = _data->GetIntersectionPoint() + (_data->GetIntersectionNormal() * 0.001f);
    /// The direction of the reflection is calculated from the law of reflection.
    glm::vec3 reflectDirection = _ray->GetDirection() - (2.0f * glm::dot(_ray->GetDirection(), _data->GetIntersectionNormal()) * _data->GetIntersectionNormal());
    return std::make_shared<Ray>(reflectOrigin, reflectDirection);
}

std::shared_ptr<Ray> Raytracer::CreateTransmissionRay(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data)
{
    /// Reference for the refraction methods: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
    glm::vec3 intersectionNormal = _data->GetIntersectionNormal();
    /// Set the refractive index of the intersected material as the transmission refractive index.
    float etaTransmission = _object->GetMaterial()->GetRefractiveIndex();
    /// Set the refractive index of the ray intersecting the object (1.0f as approximation for air).
    float etaIncident = 1.0f;
    /// Calculate the cosine of the angle of the incident.
    float cosIncident = glm::dot(_ray->GetDirection(), _data->GetIntersectionNormal());
    /// Set the bias for the transmission ray.
    glm::vec3 bias = intersectionNormal * 0.001f;

    if (cosIncident < 0.0f)
    {
        /** If the cosine of the angle of the incident is below 0, it means that
         *  the incident ray has hit the object from the outside.
         *
         *  We need to change the sign of the cosine to be positive for later calculations
         *  and set the bias to be negative to ensure that the transmission ray will not originate
         *  inside of the object. */
        cosIncident = -cosIncident;
        bias = -bias;
    }

    else
    {
        /** Otherwise, it means that the incident ray has hit the object from its inside.
         *
         *  We need to swap the incides of refraction, as the transmission ray will be leaving the
         *  object (we approximate the refractive index of air to be 1.0f), and reverse the normal
         *  to be on the opposite side of the sphere. */
        intersectionNormal = -intersectionNormal;
        etaIncident = etaTransmission;
        etaTransmission = 1.0f;
    }

    /// Calculate the total refractive index.
    float eta = etaIncident / etaTransmission;
    /** Check whether the angle of incident is higher than the "critical angle" by
     *  checking whether a term of the refraction equation is lower than 0. */
    float refractionLight = 1.0f - (eta * eta) * (1.0f - cosIncident * cosIncident);

    if (refractionLight < 0.0f)
    {
        /// Total internal reflection, no refraction in this case - return.
        return nullptr;
    }

    else
    {
        /// Set the origin of the transmission ray with a varying offset.
        glm::vec3 transmissionOrigin = _data->GetIntersectionPoint() + bias;
        /** Calculate and set the direction of the transmission ray depending on whether the incident ray
         *  is inside or outside the surface, the angle of the intersection and its total refractive index. */
        glm::vec3 transmissionDirection = (_ray->GetDirection() + cosIncident * intersectionNormal) * eta - intersectionNormal * glm::sqrt(refractionLight);
        return std::make_shared<Ray>(transmissionOrigin, transmissionDirection); ///< Returns the transmission ray.
    }
}

glm::vec3 Raytracer::RayTrace(std::shared_ptr<Ray> _ray, std::shared_ptr<Scene> _scene, int _depth)
{
    if (_depth > _scene->GetMaxDepth())
    {
        return glm::vec3(0.0f, 0.0f, 0.0f); ///< If a reflection or transmission ray has exceeded the depth limit, return the background colour.
    }

    std::vector<std::shared_ptr<Object>>::iterator objIterator;
    std::vector<std::shared_ptr<Object>>::iterator storeObj;
    std::shared_ptr<IntersectionData> data;
    std::shared_ptr<IntersectionData> storeData;

    bool anythingHit = false;
    float nearestDistance = FLT_MAX; ///< Set the initial distance to a closest intersecting object to the highest possible value.

	/// Loop through all objects in the scene.
    for (objIterator = _scene->GetObjects()->begin(); objIterator != _scene->GetObjects()->end(); objIterator++)
    {
        data = (*objIterator)->Intersect(_ray);

        if (data->HasIntersected())
        {
            if (!anythingHit)
            {
                anythingHit = true; ///< As an intersection has been detected, this bool stops the function from returning the background colour.
            }

			/// Checks if the intersected object is closer than the previous one, if multiple intersecting objects have been detected.
            if (nearestDistance > data->GetIntersectionDistance())
            {
                nearestDistance = data->GetIntersectionDistance(); ///< Change the control value to the distance to the new closest intersecting object.
                storeObj = objIterator; ///< Stores the pointer to the closest intersecting object.
                storeData = std::make_shared<IntersectionData>(*data); ///< Stores the intersection data for the object as well.
            }
        }
    }

    if (anythingHit)
    {
        glm::vec3 colour = ShadePixel(_ray, (*storeObj), storeData, _scene, _depth); ///< Shades the pixel, using the material properties of the intersected object.

        return colour;
    }

    else
    {
        return glm::vec3(0.0f, 0.0f, 0.0f); ///< Returns the background colour if no intersection has been detected for this ray.
    }
}

glm::vec3 Raytracer::ShadePixel(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene, unsigned int _depth)
{
    if (_object->GetMaterialType() == lambertian)
    {
        return CalculateDiffuseColour(_object, _data, _scene); ///< Perform diffuse shading on the object.
    }

    else if (_object->GetMaterialType() == metal)
    {
		/// Perform diffuse shading on the object and reduce the visibility of it by its reflectivity.
        glm::vec3 colour = CalculateDiffuseColour(_object, _data, _scene) * (1.0f - _object->GetMaterial()->GetReflectivity());

		/// Create a reflection ray from the intersection point.
        std::shared_ptr<Ray> reflectionRay = CreateReflectionRay(_ray, _data);
		/// Trace the reflection ray until the depth limit and return it along with the object's colour at the intersection point.
        return colour + (RayTrace(reflectionRay, _scene, _depth + 1) * _object->GetMaterial()->GetReflectivity());
    }

    else
    {
        /** Set the initial refraction colour to background's colour, as
         *  reflection is more likely to happen than refraction. */
        glm::vec3 refractionColour = glm::vec3(0.0f, 0.0f, 0.0f);
        /// Calculates how much light should be reflected and how much transmitted using Fresnel equations.
        float reflectionRatio = CalculateFresnel(_ray, _object, _data);

        /** Checks if there is any light to be transmitted.
		 *  Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel */
        if (reflectionRatio < 1.0f)
        {
           /// Creates a transmission ray for the light transmitted.
           std::shared_ptr<Ray> transmissionRay = CreateTransmissionRay(_ray, _object, _data);
		   
           /// Check if there is no total internal reflection, nullifying the refraction.
           if (transmissionRay != nullptr)
           {
                /// Trace a transmission ray through the scene.
			   refractionColour = RayTrace(transmissionRay, _scene, _depth + 1);
           }
        }

        /// Create a reflection ray from the intersection point.
        std::shared_ptr<Ray> reflectionRay = CreateReflectionRay(_ray, _data);

        /// Trace the reflection ray until the depth limit and return it.
        glm::vec3 reflectionColour = RayTrace(reflectionRay, _scene, _depth + 1);

        /// Calculate how much of the light should be shown reflected and refracted.
        glm::vec3 colour = reflectionColour * reflectionRatio + refractionColour * (1.0f - reflectionRatio);

        /// Return the colour multiplied by the transparency of the material and its own internal colour.
        return colour * _object->GetMaterial()->GetTransparency() * _object->GetColour(_data);
    }
}
