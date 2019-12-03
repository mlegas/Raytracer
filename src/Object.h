#include <memory>
#include <glm/ext.hpp>

struct IntersectionData
{
    float m_distance;
    glm::vec3 m_point;
    glm::vec3 m_normal;
};

class Ray;

class Object
{
	protected:
		glm::vec3 m_position;
        IntersectionData m_data;
	public:
        virtual glm::vec3 shadePixel(std::shared_ptr<Ray> _ray) = 0;
        virtual bool intersect(std::shared_ptr<Ray> _ray) = 0;
		glm::vec3 getPosition();
        float getIntersectionDistance();
        void setPosition(const glm::vec3& _position);
};
