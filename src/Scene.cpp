#include "DirectionalLight.h"
#include "SphericalLight.h"
#include "Scene.h"
#include "Sphere.h"
#include "Lambertian.h"
#include "Dielectric.h"
#include "Metal.h"
#include "Plane.h"

Scene::Scene()
{
    m_maxDepth = 5;
    std::shared_ptr<Lambertian> floorMaterial = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f), 0.1f);
    std::shared_ptr<Lambertian> lambertianMat = std::make_shared<Lambertian>("Textures/Marble.jpg", 0.9f);
    std::shared_ptr<Lambertian> lambertianMat3 = std::make_shared<Lambertian>("Textures/Marble.jpg", 0.9f);
	std::shared_ptr<Lambertian> lambertianMat4 = std::make_shared<Lambertian>(glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);
	std::shared_ptr<Lambertian> lambertianMat5 = std::make_shared<Lambertian>(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f);
	std::shared_ptr<Lambertian> lambertianMat6 = std::make_shared<Lambertian>(glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);
	std::shared_ptr<Lambertian> lambertianMat7 = std::make_shared<Lambertian>(glm::vec3(1.0f, 0.0f, 1.0f), 1.0f);
    std::shared_ptr<Dielectric> dielectricMat = std::make_shared<Dielectric>(glm::vec3(0.2f, 1.0f, 0.2f), 0.1f, 0.7f);
	std::shared_ptr<Dielectric> dielectricMat2 = std::make_shared<Dielectric>(glm::vec3(1.0f, 0.2f, 0.2f), 0.1f, 0.7f);
    std::shared_ptr<Metal> metalMat = std::make_shared<Metal>(glm::vec3(0.0f, 1.0f, 1.0f), 0.8f, 0.7f);
    std::shared_ptr<Metal> metalMat2 = std::make_shared<Metal>("Textures/Ice.jpg", 0.8f, 0.7f);

    std::shared_ptr<Plane> floor = std::make_shared<Plane>(glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), floorMaterial);
    std::shared_ptr<Sphere> lambertianSphere = std::make_shared<Sphere>(glm::vec3(1.1f, 0.0f, -3.0f), 0.5f, lambertianMat);
	std::shared_ptr<Sphere> lambertianSphere3 = std::make_shared<Sphere>(glm::vec3(-1.1f, 1.0f, -3.0f), 0.5f, lambertianMat3);
	std::shared_ptr<Sphere> lambertianSphere4 = std::make_shared<Sphere>(glm::vec3(-0.3f, -0.2f, -2.5f), 0.2f, lambertianMat4);
	std::shared_ptr<Sphere> lambertianSphere5 = std::make_shared<Sphere>(glm::vec3(-0.3f, 0.2f, -2.5f), 0.2f, lambertianMat5);
	std::shared_ptr<Sphere> lambertianSphere6 = std::make_shared<Sphere>(glm::vec3(0.3f, -0.2f, -2.5f), 0.2f, lambertianMat6);
	std::shared_ptr<Sphere> lambertianSphere7 = std::make_shared<Sphere>(glm::vec3(0.3f, 0.2f, -2.5f), 0.2f, lambertianMat7);
    std::shared_ptr<Sphere> dielectricSphere = std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -4.0f), 0.5f, dielectricMat);
	std::shared_ptr<Sphere> dielectricSphere2 = std::make_shared<Sphere>(glm::vec3(1.1f, 1.0f, -3.0f), 0.5f, dielectricMat2);
    std::shared_ptr<Sphere> metalSphere = std::make_shared<Sphere>(glm::vec3(-1.1f, 0.0f, -3.0f), 0.5f, metalMat);
    std::shared_ptr<Sphere> metalSphere2 = std::make_shared<Sphere>(glm::vec3(0.0f, 1.0f, -4.0f), 0.5f, metalMat2);

    m_objects = std::make_shared<std::vector<std::shared_ptr<Object>>>();
    m_objects->push_back(floor);
    m_objects->push_back(lambertianSphere);
	m_objects->push_back(lambertianSphere3);
	m_objects->push_back(lambertianSphere4);
	m_objects->push_back(lambertianSphere5);
	m_objects->push_back(lambertianSphere6);
	m_objects->push_back(lambertianSphere7);
    m_objects->push_back(dielectricSphere);
	m_objects->push_back(dielectricSphere2);
	m_objects->push_back(metalSphere);
	m_objects->push_back(metalSphere2);

    m_lights = std::make_shared<std::vector<std::shared_ptr<Light>>>();
    std::shared_ptr<SphericalLight> light = std::make_shared<SphericalLight>(glm::vec3(0.0f, 0.0f, -2.5f), glm::vec3(1.0f, 1.0f, 1.0f), 5.0f);
    std::shared_ptr<SphericalLight> light2 = std::make_shared<SphericalLight>(glm::vec3(0.5f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 5.0f);
    std::shared_ptr<SphericalLight> light3 = std::make_shared<SphericalLight>(glm::vec3(-0.5f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 5.0f);
    std::shared_ptr<DirectionalLight> light4 = std::make_shared<DirectionalLight>(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
    m_lights->push_back(light);
    m_lights->push_back(light2);
    m_lights->push_back(light3);
    m_lights->push_back(light4);
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
