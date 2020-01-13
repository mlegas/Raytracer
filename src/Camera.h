/** @file Camera.h
 *  @brief Camera class for converting screen coordinates to world space.
 */
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <memory>

class Ray;

class Camera
{
private:
    float m_aspectRatio;
    float m_fovFactor;
    glm::vec2 m_windowSize;
    glm::mat4 m_view;
	glm::mat4 m_inverseView;
	
public:
	/** @brief Creates a ray to the specified pixel coordinates using the viewing matrix.
	 *  @param _pixelCoords Pixel coordinates.
	 */
    std::shared_ptr<Ray> CreateRay(glm::vec2 _pixelCoords);
	/** @brief Constructs a camera, which sets the aspect ratio from window's size and calculates the fov factor for projecting.
	 *  @param _windowSize The height and width of the window.
	 *  @param _fov Field of view.
	 */
    Camera(glm::vec2 _windowSize, float _fov);
};
