//#include "Texture.h"
#include "IntersectionData.h"
#include "Material.h"
#include <mutex>
#include <memory>
#include <glm/vec3.hpp>

class Ray;
//class Texture;

class Object
{
	protected:
        glm::vec3 m_position;
        Material m_material;
        glm::vec3 m_albedo;
      //  Texture m_texture;
	public:
        virtual glm::vec3 shadePixel(std::shared_ptr<Ray> _ray) = 0;
        virtual std::shared_ptr<IntersectionData> intersect(std::shared_ptr<Ray> _ray) = 0;
        glm::vec3 getAlbedo();
		glm::vec3 getPosition();
        void setPosition(const glm::vec3& _position);
};
