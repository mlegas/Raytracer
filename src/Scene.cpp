#include "DirectionalLight.h"
#include "SphericalLight.h"
#include "Scene.h"
#include "Sphere.h"
#include "Dielectric.h"

Scene::Scene()
{
    m_maxDepth = 5;
    std::shared_ptr<Material> material = std::make_shared<Dielectric>(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f);

    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(2.0f, 0.0f, -6.0f), 2.0f, material);
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(glm::vec3(-1.0f, 0.0f, -6.0f), 0.5f, material);

    m_objects = std::make_shared<std::vector<std::shared_ptr<Object>>>();
    m_objects->push_back(sphere);
    m_objects->push_back(sphere2);

    m_lights = std::make_shared<std::vector<std::shared_ptr<Light>>>();
    std::shared_ptr<SphericalLight> light = std::make_shared<SphericalLight>(glm::vec3(-1.0f, 0.0f, -5.4f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0f);
    m_lights->push_back(light);
}

std::shared_ptr<std::vector<std::shared_ptr<Object>>> Scene::GetObjects()
{
    return m_objects;
}

std::shared_ptr<std::vector<std::shared_ptr<Light>>> Scene::GetLights()
{
    return m_lights;
}

unsigned int Scene::GetMaxDepth()
{
    return m_maxDepth;
}
