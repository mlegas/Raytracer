#include <cfloat>
#include <iostream>
#include <glm/ext.hpp>
#include "Light.h"
#include "Raytracer.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"

glm::vec3 Raytracer::rayTrace(std::shared_ptr<Ray> _ray, std::shared_ptr<Scene> _scene)
{
    std::vector<std::shared_ptr<Object>>::iterator objIterator;
    std::vector<std::shared_ptr<Object>>::iterator storeObj;

	bool anythingHit = false;
    float nearestDistance = FLT_MAX;

    for (objIterator = _scene->getObjects()->begin(); objIterator != _scene->getObjects()->end(); objIterator++)
	{
        if ((*objIterator)->intersect(_ray))
        {
            if (!anythingHit)
            {
                anythingHit = true;
            }

            if (nearestDistance > (*objIterator)->getIntersectionDistance())
            {
                nearestDistance = (*objIterator)->getIntersectionDistance();
                storeObj = objIterator;
            }
        }
	}

    if (anythingHit)
	{
        glm::vec3 colour = (*storeObj)->shadePixel(_ray) * computeLighting(_scene, *storeObj, -_ray->getDirection());

        colour = glm::vec3(glm::clamp((colour.x * 255.0f), 0.0f, 255.0f),
                           glm::clamp((colour.y * 255.0f), 0.0f, 255.0f),
                           glm::clamp((colour.z * 255.0f), 0.0f, 255.0f));

        return colour;
    }

    else
    {
        return glm::vec3(255.0f, 255.0f, 255.0f);
    }
}

glm::vec3 Raytracer::computeLighting(std::shared_ptr<Scene> _scene, std::shared_ptr<Object> _object, glm::vec3 _direction)
{
    std::vector<std::shared_ptr<Light>>::iterator lightIterator;
    glm::vec3 totalLight(0.0f);

    for (lightIterator = _scene->getLights()->begin(); lightIterator != _scene->getLights()->end(); lightIterator++)
    {
       if ((*lightIterator)->getLightType() == ambient)
       {
           totalLight += (*lightIterator)->getLightIntensity();
       }

       else
       {
           glm::vec3 intersectionToLight;

           if ((*lightIterator)->getLightType() == spherical)
           {
               intersectionToLight = (*lightIterator)->getPosition() - _object->getIntersectionPoint();
           }

           else
           {
               intersectionToLight = (*lightIterator)->getDirection();
           }

           glm::vec3 lightRay = glm::normalize(intersectionToLight);

           // Diffuse
           float diffuseProjection = glm::dot(lightRay, _object->getIntersectionNormal());

           if (diffuseProjection > 0.0f)
           {
                totalLight += (*lightIterator)->getLightIntensity() * diffuseProjection;
           }

            // Specular
            if (_object->getSpecular() >= 0.0f)
            {
                glm::vec3 reflectedRay = 2.0f * _object->getIntersectionNormal() * glm::dot(_object->getIntersectionNormal(), lightRay) - intersectionToLight;
                float specularProjection = glm::dot(reflectedRay, _direction);

                if (specularProjection > 0.0f)
                {
                    totalLight += (*lightIterator)->getLightIntensity() * static_cast<float>(pow(specularProjection, _object->getSpecular()));
                }
            }
       }
       totalLight += totalLight * (*lightIterator)->getLightColour();
    }

    return totalLight;
}
