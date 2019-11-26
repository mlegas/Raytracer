#include "Raytracer.h"
#include "Ray.h"
#include "Scene.h"

glm::vec3 Raytracer::RayTrace(std::shared_ptr<Ray> _ray, std::shared_ptr<Scene> _scene)
{
	std::vector<std::shared_ptr<Object>>::iterator objIt;
	
	std::shared_ptr<IntersectionData> data;
	
	float shortestDistance = FLT_MAX;
	
	bool anythingHit = false;
	
	std::vector<glm::vec3>::iterator shortestDistPoint;
	std::vector<std::shared_ptr<Object>>::iterator shortestDistObj;
	
	for (objIt = _scene->getObjects().begin(); objIt != _scene->getObjects().end(); objIt++)
	{
		data = _ray->SphereIntersection(*objIt);
		
		if (data->m_intersection)
		{
			std::vector<glm::vec3>::iterator vecIt;
			
			for (vecIt = data->m_points.begin(); vecIt != data->m_points.end(); vecIt++)
			{
				float tempDistanceSquared = glm::dot(*vecIt, *vecIt);
				if (tempDistanceSquared < shortestDistance)
				{
					anythingHit = true;
					shortestDistance = tempDistanceSquared;
					shortestDistPoint = vecIt;
					shortestDistObj = objIt;
				}
			}
		}
	}
	
	// get shortest distance from origin to intersection point
	// call this object's shade function (return glm::vec3)
	
	if (anythingHit)
	{
		return *shortestDistObj->shadePixel(_ray, *shortestDistPoint);
	}
	
	else
	{
		return glm::vec3(0,0,0);
	}

}

Raytracer::Raytracer()
{
}


Raytracer::~Raytracer()
{
}
