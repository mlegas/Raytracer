/** @file Camera.cpp
 *  @brief Implementation of functions for the Camera class.
 */

#include "Camera.h"
#include "Ray.h"
#include <glm/ext.hpp>

std::shared_ptr<Ray> Camera::CreateRay(glm::vec2 _pixelCoords)
{
    /** Convert the pixel coordinates to camera space, taking the FOV and aspect ratio into consideration.
     *  The 0.5f is added to set the ray towards the middle of the pixel, however the use of anti-aliasing instead just
     *  ensures that the ray stays inside of the pixel.
     *  Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays */
    float cameraX = (2.0f * ((_pixelCoords.x + 0.5f) / m_windowSize.x) - 1.0f) * m_fovFactor * m_aspectRatio;
    float cameraY = (1.0f - 2.0f * ((_pixelCoords.y + 0.5f) / m_windowSize.y)) * m_fovFactor;

    glm::vec4 origin = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 direction = glm::vec4(cameraX, cameraY, -1.0f, 1.0f); ///< Point the direction towards negative Z.

    /// Convert from camera to world space.
    origin = origin * m_inverseView;
    direction = direction * m_inverseView;

    /// Return a ray. The direction will be normalized in the constructor of Ray.
    std::shared_ptr<Ray> ray = std::make_shared<Ray>(origin, direction);
    return ray;
}

Camera::Camera(glm::vec2 _windowSize, float _fov)
{
    m_windowSize = _windowSize;

    /// Calculate the aspect ratio.
    m_aspectRatio = m_windowSize.x / m_windowSize.y;

    /** Calculate the fov factor to project the view.
     *  Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays */
    m_fovFactor = glm::tan(glm::radians(_fov) / 2.0f);

    /// Set the viewing matrix.
    m_view = glm::lookAt(
                 glm::vec3(0, 0, 0), ///< Origin of the camera.
                 glm::vec3(0, 0, -1), ///< Direction of the camera.
                 glm::vec3(0, 1, 0)); ///< This sets the camera to look up.

    m_inverseView = glm::inverse(m_view); ///< Used for convertion from camera to world space.
}
