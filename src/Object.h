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
    public:
        virtual std::shared_ptr<IntersectionData> Intersect(std::shared_ptr<Ray> _ray) = 0;
        glm::vec3 GetPosition();
        float GetAlbedo();
        glm::vec3 GetColour();
        float GetReflectivity();
        float GetRefractiveIndex();
        float GetTransparency();
        MaterialType GetMaterialType();
};

#endif
