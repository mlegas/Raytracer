#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "IntersectionData.h"
#include "Material.h"
#include <mutex>
#include <memory>
#include <glm/vec3.hpp>

class Scene;
class Ray;

class Object
{
	protected:
        glm::vec3 m_position;
        std::shared_ptr<Material> m_material;
        virtual glm::vec3 GetTextureColour(std::shared_ptr<IntersectionData> _data) {}
    public:
        virtual std::shared_ptr<IntersectionData> Intersect(std::shared_ptr<Ray> _ray) = 0;
        glm::vec3 GetColour(std::shared_ptr<IntersectionData> _data);
        glm::vec3 GetPosition();
        MaterialType GetMaterialType();
        std::shared_ptr<Material> GetMaterial();
};

#endif
