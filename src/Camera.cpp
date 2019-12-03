#include "Camera.h"
#include "Ray.h"

Ray Camera::CreateRay(glm::ivec2 _pixelCoords)
{
    // raster space to NDC

    float ndcX = (_pixelCoords.x + 0.5f) / m_windowSize.x;
    float ndcY = (_pixelCoords.y + 0.5f) / m_windowSize.y;

    // NDC to screen space

    float screenX = (2.0f * ndcX) - 1.0f;
    float screenY = 1.0f - (2.0f * ndcY);

    // screen space to camera space using projection

    float cameraX = (2.0f * screenX - 1.0f) * m_aspectRatio * m_fovFactor;
    float cameraY = (1.0f - (2.0f * screenY)) * m_fovFactor;

    glm::vec4 origin = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 direction = glm::vec4(cameraX, cameraY, -1.0f, 1.0f); ///< point the direction towards negative Z

    // from camera to world space

    origin = origin * glm::inverse(m_view);
    direction = direction * glm::inverse(m_view);

    glm::vec3 dir = glm::vec3(glm::normalize(direction));

    Ray ray(origin, dir);
	return ray;
}

Camera::Camera(glm::ivec2 _windowSize, float _fov)
{
	m_windowSize = _windowSize;

    m_aspectRatio = m_windowSize.x / m_windowSize.y;

    m_fovFactor = glm::tan(glm::radians(_fov) / 2.0f);

    m_view = glm::lookAt(
        glm::vec3(0, 0, 0), ///< This is the origin of the camera.
        glm::vec3(0, 0, -1), ///< This is the direction of the camera, where the camera looks at.
        glm::vec3(0, 1, 0)); ///< This sets the camera to look up.
}


Camera::~Camera()
{
}
