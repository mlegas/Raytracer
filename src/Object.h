//#include "Texture.h"
#include "IntersectionData.h"
#include <memory>
#include <glm/vec3.hpp>

class Ray;
//class Texture;

class Object
{
	protected:
		glm::vec3 m_position;
        IntersectionData m_data;
      //  Texture m_texture;
	public:
        virtual glm::vec3 shadePixel(std::shared_ptr<Ray> _ray) = 0;
        virtual bool intersect(std::shared_ptr<Ray> _ray) = 0;
		glm::vec3 getPosition();
        float getIntersectionDistance();
        glm::vec3 getIntersectionNormal();
        glm::vec3 getIntersectionPoint();
        void setPosition(const glm::vec3& _position);
};
