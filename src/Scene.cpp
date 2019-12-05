#include "Scene.h"
#include "Sphere.h"

Scene::Scene()
{
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -10.0f), 1.0f);
	m_objects = std::make_shared<std::vector<std::shared_ptr<Object>>>();
	m_objects->push_back(sphere);
}

std::shared_ptr<std::vector<std::shared_ptr<Object>>> Scene::getObjects()
{
    return m_objects;
}
