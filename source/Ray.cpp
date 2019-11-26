#include "Ray.h"
#include <cmath>
#include <limits>
#include <memory>

glm::vec3 Ray::ClosestPoint(glm::vec3 _queryPoint)
{
	m_normalizedDirection = glm::normalize(m_direction);
	m_lengthOnLine = glm::dot((_queryPoint - m_origin), m_normalizedDirection);
	glm::vec3 closestPoint = m_origin + (m_lengthOnLine * m_normalizedDirection);
	return closestPoint;
}

IntersectionData Ray::SphereIntersection(std::shared_ptr<Sphere> _sphere)
{
	std::shared_ptr<IntersectionData> data;
	
	glm::vec3 distanceFromOrigin = glm::vec3(m_origin - _sphere->getCentre());
	float distanceSquared = glm::dot(distanceFromOrigin, distanceFromOrigin);
	float radiusSquared = _sphere->getRadius() * _sphere->getRadius();
	
	//check if ray origin is inside sphere
	if (distanceSquared > radiusSquared)
	{
		glm::vec3 point = ClosestPoint(_ray, _sphere);
		
		// check if sphere is behind ray
		if (glm::dot(m_direction, point) <= 0.0f)
		{
			data->m_intersection = false;
		}
		
		else 
		{
			//get the distance from closest point on line to sphere's centre
			glm::vec3 distanceFromPoint = glm::vec3(point - _sphere->getCentre());
			
			//now proper intersection tests begin
			distanceSquared = glm::dot(distanceFromPoint, distanceFromPoint);
			
			//check if point is inside sphere
			if (distanceSquared > radiusSquared)
			{
				data->m_intersection = false;
			}
			
			// check if intersection point is on sphere's edge
			else if (fabs(distanceSquared - radiusSquared) < std::numeric_limits<float>::epsilon())
			{
				data->m_intersection = true;
				data->m_points.push_back(point);
			}
			
			else
			{
				float d = glm::length(_sphere->getCentre() - m_origin - (m_lengthOnLine * m_normalizedDirection));
				float x = sqrt(radiusSquared - (d * d));
				
				data->m_intersection = true;
				data->m_points.push_back(m_origin + (m_lengthOnLine - x) * m_normalizedDirection);
				data->m_points.push_back(m_origin + (m_lengthOnLine + x) * m_normalizedDirection);
			}
		}
	}
	
	else
	{
		data.m_intersection = false;
	}
	
	return data;
}

Ray::Ray(glm::vec3 _origin, glm::vec3 _direction)
{
	m_origin = _origin;
	m_direction = _direction;
}
