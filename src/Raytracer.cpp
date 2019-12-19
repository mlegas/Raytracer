#include <cfloat>
#include <iostream>
#include <glm/ext.hpp>
#include "Light.h"
#include "Raytracer.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"

glm::vec3 Raytracer::RayTrace(std::shared_ptr<Ray> _ray, std::shared_ptr<Scene> _scene)
{
    std::vector<std::shared_ptr<Object>>::iterator objIterator;
    std::vector<std::shared_ptr<Object>>::iterator storeObj;
    std::shared_ptr<IntersectionData> data;
    std::shared_ptr<IntersectionData> storeData;

	bool anythingHit = false;
    float nearestDistance = FLT_MAX;

    for (objIterator = _scene->GetObjects()->begin(); objIterator != _scene->GetObjects()->end(); objIterator++)
    {
        data = (*objIterator)->Intersect(_ray);

        if (data->HasIntersected())
        {
            if (!anythingHit)
            {
                anythingHit = true;
            }

            if (nearestDistance > data->GetIntersectionDistance())
            {
                nearestDistance = data->GetIntersectionDistance();
                storeObj = objIterator;
                storeData = std::make_shared<IntersectionData>(*data);
            }
        }
	}

    if (anythingHit)
	{        
        glm::vec3 colour = (*storeObj)->ShadePixel(storeData, _scene);

        colour = glm::vec3(glm::clamp((colour.x * 255.0f), 0.0f, 255.0f),
                           glm::clamp((colour.y * 255.0f), 0.0f, 255.0f),
                           glm::clamp((colour.z * 255.0f), 0.0f, 255.0f));

        return colour;
    }

    else
    {
        return glm::vec3(50.0f, 50.0f, 50.0f);
    }
}

glm::vec3 Raytracer::Reflect(std::shared_ptr<Ray> _ray, std::shared_ptr<IntersectionData> _data)
{
        return _ray->GetDirection() - 2.0f * glm::dot(_ray->GetDirection(), _data->GetIntersectionPoint()) * _data->GetIntersectionPoint();
}
