#include <cfloat>
#include <iostream>
#include <glm/ext.hpp>
#include "Light.h"
#include "Object.h"
#include "Raytracer.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"

glm::vec3 Raytracer::CalculateDiffuseColour(std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene)
{
    std::vector<std::shared_ptr<Light>>::iterator lightIterator;
    glm::vec3 totalLight(0.0f);

    for (lightIterator = _scene->GetLights()->begin(); lightIterator != _scene->GetLights()->end(); lightIterator++)
    {
        totalLight = totalLight + _object->GetColour(_data) * (*lightIterator)->CalculateLight(_data, _scene->GetObjects(), _object->GetAlbedo());
    }

    return totalLight;
}

float Raytracer::CalculateFresnel(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data)
{
    float dirProjection = glm::dot(_ray->GetDirection(), _data->GetIntersectionNormal());
    float etaIncident = 1.0f;
    float etaTransmission = _object->GetRefractiveIndex();

    if (dirProjection > 0.0f)
    {
        etaIncident = etaTransmission;
        etaTransmission = 1.0f;
    }

    float sinTransmission = etaIncident / etaTransmission * glm::sqrt(std::max((1.0f - dirProjection * dirProjection), 0.0f));

    if (sinTransmission > 1.0f)
    {
        //Total internal reflection
        return 1.0f;
    }

    else
    {
        float cosTransmission = glm::sqrt(std::max((1.0f - sinTransmission * sinTransmission), 0.0f));
        float cosIncident = glm::abs(cosTransmission);

        float rs = ((etaTransmission * cosIncident) - (etaIncident * cosTransmission)) /
                ((etaTransmission * cosIncident) + (etaIncident * cosTransmission));
        float rp = ((etaIncident * cosIncident) - (etaTransmission * cosTransmission)) /
                ((etaIncident * cosIncident) + (etaTransmission * cosTransmission));

        return (rs * rs + rp * rp) / 2.0f;
    }
}

std::shared_ptr<Ray> Raytracer::CreateReflectionRay(std::shared_ptr<Ray> _ray, std::shared_ptr<IntersectionData> _data)
{
    glm::vec3 reflectOrigin = _data->GetIntersectionPoint() + (_data->GetIntersectionNormal() * 0.01f);
    glm::vec3 reflectDirection = _ray->GetDirection() - (2.0f * glm::dot(_ray->GetDirection(), _data->GetIntersectionNormal()) * _data->GetIntersectionNormal());
    return std::make_shared<Ray>(reflectOrigin, reflectDirection);
}

std::shared_ptr<Ray> Raytracer::CreateTransmissionRay(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data)
{
    glm::vec3 intersectionNormal = _data->GetIntersectionNormal();
    float etaTransmission = _object->GetRefractiveIndex();
    float etaIncident = 1.0f;
    float dirProjection = glm::dot(_ray->GetDirection(), _data->GetIntersectionNormal());

    if (dirProjection < 0.0f)
    {
        // Outside the surface, we want cos(theta) to be positive
        dirProjection = -dirProjection;
    }

    else
    {
        // We are inside the surface, cos(theta) is already positive but reverse normal direction
        // Invert the normal and swap the indices of refraction
        intersectionNormal = -intersectionNormal;
        etaIncident = etaTransmission;
        etaTransmission = 1.0f;
    }

    float eta = etaIncident / etaTransmission;
    float reflectionRatio = 1.0f - (eta * eta) * (1.0f - dirProjection * dirProjection);

    if (reflectionRatio < 0.0f)
    {
        // total internal reflection. There is no refraction in this case
        return nullptr;
    }

    else
    {
        glm::vec3 transmissionOrigin = _data->GetIntersectionPoint() + (intersectionNormal * 0.01f);
        glm::vec3 transmissionDirection = (_ray->GetDirection() + dirProjection * intersectionNormal) * eta - intersectionNormal * glm::sqrt(reflectionRatio);
        return std::make_shared<Ray>(transmissionOrigin, transmissionDirection);
    }
}

glm::vec3 Raytracer::RayTrace(std::shared_ptr<Ray> _ray, std::shared_ptr<Scene> _scene, unsigned int _depth)
{
    if (_depth > _scene->GetMaxDepth())
    {
        return glm::vec3(0.0f, 0.0f, 0.0f);
    }

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
        glm::vec3 colour = ShadePixel(_ray, (*storeObj), storeData, _scene, _depth);

        colour = glm::vec3(glm::clamp((colour.x * 255.0f), 0.0f, 255.0f),
                           glm::clamp((colour.y * 255.0f), 0.0f, 255.0f),
                           glm::clamp((colour.z * 255.0f), 0.0f, 255.0f));

        return colour;
    }

    else
    {
        return glm::vec3(0.0f, 0.0f, 0.0f);
    }
}

glm::vec3 Raytracer::ShadePixel(std::shared_ptr<Ray> _ray, std::shared_ptr<Object> _object, std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene, unsigned int _depth)
{
    if (_object->GetMaterialType() == lambertian)
    {
        return CalculateDiffuseColour(_object, _data, _scene);
    }

    else if (_object->GetMaterialType() == metal)
    {
        glm::vec3 colour = CalculateDiffuseColour(_object, _data, _scene) * (1.0f - _object->GetReflectivity());

        std::shared_ptr<Ray> reflectionRay = CreateReflectionRay(_ray, _data);
        return colour + (RayTrace(reflectionRay, _scene, _depth + 1) * _object->GetReflectivity());
    }

    else
    {
        glm::vec3 refractionColour = glm::vec3(0.0f, 0.0f, 0.0f);
        float reflectionRatio = CalculateFresnel(_ray, _object, _data);

        if (reflectionRatio < 1.0f)
        {
           std::shared_ptr<Ray> transmissionRay = CreateTransmissionRay(_ray, _object, _data);

           if (transmissionRay != nullptr)
           {
                refractionColour = RayTrace(transmissionRay, _scene, _depth + 1);
           }
        }

        std::shared_ptr<Ray> reflectionRay = CreateReflectionRay(_ray, _data);
        glm::vec3 reflectionColour = RayTrace(reflectionRay, _scene, _depth + 1);

        glm::vec3 colour = reflectionColour * reflectionRatio + refractionColour * (1.0f - reflectionRatio);
        return colour * _object->GetTransparency() * _object->GetColour(_data);
    }

}
