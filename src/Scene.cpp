#include "Light.h"
#include "Scene.h"
#include "Sphere.h"

Scene::Scene()
{
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -5.0f), 1.0f, 10.0f);
	m_objects = std::make_shared<std::vector<std::shared_ptr<Object>>>();
	m_objects->push_back(sphere);

    m_lights = std::make_shared<std::vector<std::shared_ptr<Light>>>();
    std::shared_ptr<Light> light2 = std::make_shared<Light>(1.0f, glm::vec3(0.0f, 0.0f, -1.0f));
   // std::shared_ptr<Light> light3 = std::make_shared<Light>(glm::vec3(0.0f, 2.0f, -3.0f), glm::vec3(255.0f, 255.0f, 255.0f), 0.2f);
    m_lights->push_back(light2);
   // m_lights->push_back(light3);
}

std::shared_ptr<std::vector<std::shared_ptr<Object>>> Scene::getObjects()
{
    return m_objects;
}

std::shared_ptr<std::vector<std::shared_ptr<Light>>> Scene::getLights()
{
    return m_lights;
}
