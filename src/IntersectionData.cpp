#include "IntersectionData.h"

float IntersectionData::getIntersectionDistance()
{
    return m_distance;
}

glm::vec3 IntersectionData::getIntersectionNormal()
{
    return m_normal;
}

glm::vec3 IntersectionData::getIntersectionPoint()
{
    return m_point;
}

bool IntersectionData::hasIntersected()
{
    return m_intersection;
}

IntersectionData::IntersectionData(bool _intersection)
{
    m_intersection = _intersection;
}

IntersectionData::IntersectionData(bool _intersection, float _distance, glm::vec3 _point, glm::vec3 _normal)
{
    m_intersection = _intersection;
    m_distance = _distance;
    m_point = _point;
    m_normal = _normal;
}
