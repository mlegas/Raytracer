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
        return (*storeObj)->shadePixel(_ray) * computeLighting(_scene, *storeObj);
	}

    else
    {
        return glm::vec3(255.0f,255.0f,255.0f);
    }
}

glm::vec3 Raytracer::computeLighting(std::shared_ptr<Scene> _scene, std::shared_ptr<Object> _object)
{
    std::vector<std::shared_ptr<Light>>::iterator lightIterator;
    glm::vec3 i(0.0f, 0.0f, 0.0f);

    for (lightIterator = _scene->getLights()->begin(); lightIterator != _scene->getLights()->end(); lightIterator++)
    {
       if ((*lightIterator)->getLightType() == ambient)
       {
           i += (*lightIterator)->getLight();
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

           float lightProjection = glm::dot(glm::normalize(intersectionToLight), _object->getIntersectionNormal());

           if (lightProjection > 0.0f)
           {
                i += (*lightIterator)->getLight() * lightProjection;
           }
       }
    }

    return i;
}
