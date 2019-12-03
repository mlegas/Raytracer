#include "Raytracer.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"

glm::vec3 Raytracer::RayTrace(const Ray &_ray, std::shared_ptr<Scene> _scene)
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
        return (*storeObj)->shadePixel(_ray);
	}

    else
    {
        return glm::vec3(255.0f,255.0f,255.0f);
    }
}
