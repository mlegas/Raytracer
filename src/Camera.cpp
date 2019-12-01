#include "Camera.h"
#include "Ray.h"

std::shared_ptr<Ray> Camera::CreateRay(glm::ivec2 _pixelCoords)
{
	// change range using https://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
	// NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin

	float ndcX = ((_pixelCoords.x * 2) / m_windowSize.x) - 1;
	float ndcY = -(((_pixelCoords.y * 2) / m_windowSize.y) - 1);

    // WRONG CONVERSION TO NDC - FIX PLS
	glm::vec4 origin = glm::vec4(ndcX, ndcY, -1, 1);
	glm::vec4 direction = glm::vec4(ndcX, ndcY, 1, 1);

	origin = origin * glm::inverse(m_projection);
	direction = direction * glm::inverse(m_projection);

	origin = glm::vec4(origin.x/origin.w, origin.y/origin.w, origin.z/origin.w, 1);
	direction = glm::vec4(direction.x/direction.w, direction.y/direction.w, direction.z/direction.w, 1);

	origin = origin * glm::inverse(m_view);
	direction = direction * glm::inverse(m_view);

	std::shared_ptr<Ray> ray = std::make_shared<Ray>(origin, direction);
	return ray;
}

Camera::Camera(glm::ivec2 _windowSize)
{
	m_windowSize = _windowSize;

    m_projection = glm::perspective(glm::radians(80.0f), static_cast<float>(_windowSize.x) / static_cast<float>(_windowSize.y), 0.1f, 100.f);

	m_view = glm::lookAt(
		glm::vec3(0, 0, 0), ///< This is the origin of the camera.
		glm::vec3(0, 0, 1), ///< This is the direction of the camera, where the camera looks at.
		glm::vec3(0, 1, 0)); ///< This sets the camera to look up.
}


Camera::~Camera()
{
}
