#include "Scene.h"
#include "Sphere.h"

Scene::Scene()
{
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(0,0, 10), 5);
	m_objects.push_back(sphere);
}

std::vector<std::shared_ptr<Object>> Scene::getObjects()
{
    return m_objects;
}
