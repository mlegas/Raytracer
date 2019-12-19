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
        float m_albedo;
        glm::vec3 CalculateDiffuseColour(std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene);
    public:
        glm::vec3 ShadePixel(std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene);
        virtual std::shared_ptr<IntersectionData> Intersect(std::shared_ptr<Ray> _ray) = 0;
        glm::vec3 GetPosition();
        MaterialType GetMaterialType();
        void SetPosition(const glm::vec3& _position);
};

#endif
