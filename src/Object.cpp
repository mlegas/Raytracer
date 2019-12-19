#include "Light.h"
#include "Scene.h"
#include "Object.h"

glm::vec3 Object::GetPosition()
{
	return m_position;
}

void Object::SetPosition(const glm::vec3 &_position)
{
	m_position = _position;
}

MaterialType Object::GetMaterialType()
{
    return m_material->GetMaterialType();
}

glm::vec3 Object::CalculateDiffuseColour(std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene)
{
    std::vector<std::shared_ptr<Light>>::iterator lightIterator;
    glm::vec3 totalLight(0.0f);

    for (lightIterator = _scene->GetLights()->begin(); lightIterator != _scene->GetLights()->end(); lightIterator++)
    {
        totalLight = totalLight + m_material->GetColour() * (*lightIterator)->CalculateLight(_data, _scene->GetObjects(), m_material->GetAlbedo());
    }

    return totalLight;
}

glm::vec3 Object::ShadePixel(std::shared_ptr<IntersectionData> _data, std::shared_ptr<Scene> _scene)
{
    /* shade pixel:
     * depending on material
     * 1. Lambertian - light * albedo (possible blinn-phong implementation with modifying the normals) [actually fuck off with blinn phong lmao]
     * 2. Dielectric - reflection: light * reflection
     * 3. Metal - refraction * reflection (without light)
     * now how to implement???
     * ShadePixel: if material then
     * diffuse: calculate colour of the point (intersection data) against all lights, check against all objects if in shadow (scene in use)
     * dielectric: calculate colour of the point using diffuse (diffuse function in need that will take scene and data), reflect
     * metal: refract and reflect
     * do we need geometry class? kind of, maybe not
     * only normals for data are changed so only intersect functions need to change
     * implement diffuse in Object class? YES
     */

    if (m_material->GetMaterialType() == lambertian)
    {
        return CalculateDiffuseColour(_data, _scene);
    }

    else if (m_material->GetMaterialType() == dielectric)
    {

    }

    else
    {

    }

}
