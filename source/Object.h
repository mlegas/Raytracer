#include <memory>
#include <glm/ext.hpp>

class Ray;

class Object
{
	private:
		glm::vec3 m_position;
	public:
		virtual glm::vec3 shadePixel(std::shared_ptr<Ray> _ray, glm::vec3 _intersectionPoint);
		glm::vec3 getPosition();
		void setPosition(glm::vec3 _position);
};