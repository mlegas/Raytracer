#include "DirectionalLight.h"
#include "SphericalLight.h"
#include "Scene.h"
#include "Sphere.h"

Scene::Scene()
{
    std::shared_ptr<Material> material = std::make_shared<Material>(1.0f, glm::vec3(0.0f, 0.2f, 0.5f));
    std::shared_ptr<Material> material2 = std::make_shared<Material>(1.0f, glm::vec3(0.5f, 0.0f, 0.5f));

    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(2.0f, 0.0f, -6.0f), 2.0f, material);
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(glm::vec3(-1.0f, 0.0f, -6.0f), 0.5f, material2);
	m_objects = std::make_shared<std::vector<std::shared_ptr<Object>>>();
    m_objects->push_back(sphere);
    m_objects->push_back(sphere2);

    m_lights = std::make_shared<std::vector<std::shared_ptr<Light>>>();
    std::shared_ptr<SphericalLight> light = std::make_shared<SphericalLight>(glm::vec3(-1.0f, 0.0f, -5.4f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0f);
    m_lights->push_back(light);

   // m_lights->push_back(light3);
}

std::shared_ptr<std::vector<std::shared_ptr<Object>>> Scene::GetObjects()
{
    return m_objects;
}

std::shared_ptr<std::vector<std::shared_ptr<Light>>> Scene::GetLights()
{
    return m_lights;
}
