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
        glm::vec3 colour = (*storeObj)->shadePixel(_ray) * computeLighting(_scene->getLights(), *storeObj);

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

glm::vec3 Raytracer::computeLighting(std::shared_ptr<std::vector<std::shared_ptr<Light>>> _lights, std::shared_ptr<Object> _object)
{
    std::vector<std::shared_ptr<Light>>::iterator lightIterator;
    glm::vec3 totalLight(0.0f);

    for (lightIterator = _lights->begin(); lightIterator != _lights->end(); lightIterator++)
    {
       if ((*lightIterator)->getLightType() == ambient)
       {
           totalLight += (*lightIterator)->getLight();
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
                totalLight += (*lightIterator)->getLight() * diffuseProjection;
           }
       }
    }

    return totalLight;
}
