/** @file Sphere.cpp
 *	@brief Implementation of functions for the Sphere class.
 */

#include "Sphere.h"
#include "Ray.h"
#include <glm/ext.hpp>
#include <algorithm>
#include <iostream>

std::shared_ptr<IntersectionData> Sphere::Intersect(std::shared_ptr<Ray> _ray)
{
    /** I use the analytic intersection method suggested in this reference:
     *  https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection */
    glm::vec3 centerToOrigin = _ray->GetOrigin() - m_position; ///< Set the vector from the ray's origin to the sphere's position.
    /// Dot product of a vector with itself results in a square of its magnitude.
    float centerToOriginSquared = glm::dot(centerToOrigin, centerToOrigin);

    /// Set the quadratic coefficients.
    float a = 1.0f; ///< As all ray directions are normalized in Ray's constructor, 'a' can be set to 1.0f.
    float b = 2.0f * glm::dot(_ray->GetDirection(), centerToOrigin);
    float c = centerToOriginSquared - m_radiusSquared;

    float discriminant = (b * b) - (4 * a * c);

    /// Solutions to the quadratic equation.
    float t0;
    float t1;

    if (discriminant < 0.0f)
    {
        /// No quadratic solutions - no intersection, return.
        return std::make_shared<IntersectionData>(false);
    }

    /** This line checks if the discriminant is less than the epsilon of the floating point type
     *  to compare if the discriminant is equal to zero. */
    else if (discriminant < std::numeric_limits<float>::epsilon())
    {
        /// The discriminant is equal to zero, therefore there is only one solution to the quadratic equation.
        t0 = t1 = - 0.5f * b / a;
    }

    /** There are two solutions to the quadratic equation, meaning that we should use the quadratic formula
     *  to solve the equation. Due to the loss of significance happening with the use of floating point values however,
     *  we use the more stable solver proposed by Press et al.
     *  References: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
     *  https://link.springer.com/content/pdf/10.1007%2F978-1-4842-4427-2_7.pdf */
    else
    {
        float q;

        /** We use the sign of b in the calculation of q, therefore we need to check
         *  whether it is above or below 0. */
        if (b > 0.0f)
        {
            /** The calculation of q involves multiplying the discriminant
             *  by the a coefficient, however as it is equal to 1.0f, we can just skip it. */
            q = -0.5f * (b + sqrt(discriminant));
        }

        else
        {
            q = -0.5f * (b - sqrt(discriminant));
        }

        /// Calculate the quadratic formula solutions.
        t0 = q / a;
        t1 = c / q;
     }

    float t;

    if (t0 < 0.0f && t1 < 0.0f)
    {
        /// Both solutions are below zero, meaning that the intersection happened behind the ray's origin. Return false.
        return std::make_shared<IntersectionData>(false);
    }

    /// Set the solution to the one in front of the ray's origin.
    else if (t0 < 0.0f && t1 >= 0.0f)
    {
        t = t1;
    }

    else if (t0 >= 0.0f && t1 < 0.0f)
    {
        t = t0;
    }

    else
    {
        /// If both solutions are positive, check which one is closer to the ray's origin.
        if (t0 < t1)
        {
            t = t0;
        }

        else
        {
            t = t1;
        }
    }

    /// Set the intersection data and return it.
    float distance = t;
    glm::vec3 point = _ray->GetOrigin() + _ray->GetDirection() * t; ///< Set the intersection point using the ray's equation.
    glm::vec3 normal = glm::normalize(point - m_position); ///< Calculate the normal of the intersection.
    return std::make_shared<IntersectionData>(true, distance, point, normal);
}

glm::vec3 Sphere::GetTextureColour(std::shared_ptr<IntersectionData> _data)
{
    /** Reference: https://www.realtimerendering.com/raytracing/Ray%20Tracing_%20The%20Next%20Week.pdf
     *  https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection */
	float pi = 3.14159265f;

    float phi = std::atan2(_data->GetIntersectionNormal().x, _data->GetIntersectionNormal().z);
    float theta = glm::asin(_data->GetIntersectionNormal().y);
    float u = (phi + pi) / (2.0f * pi);
    float v = (theta + pi / 2.0f) / pi;

    unsigned char* data = m_material->GetTextureData();
    int width = m_material->GetTextureWidth();
    int height = m_material->GetTextureHeight();

    int i = u * width;
    int j = (1.0f - v) * height - 0.001f;

    if (i < 0)
    {
        i = 0;
    }

    else if (i > width - 1)
    {
        i = width - 1;
    }

    if (j < 0)
    {
        j = 0;
    }

    else if (j > height - 1)
    {
        j = height - 1;
    }

    float r = data[3 * i + 3 * width * j] / 255.0f;
    float g = data[3 * i + 3 * width * j + 1] / 255.0f;
    float b = data[3 * i + 3 * width * j + 2] / 255.0f;

    return glm::vec3(r, g, b);
}

Sphere::Sphere(glm::vec3 _position, float _radius, std::shared_ptr<Material> _material)
{
	m_position = _position;
	m_radius = _radius;
    m_radiusSquared = m_radius * m_radius;
    m_material = _material;
}
