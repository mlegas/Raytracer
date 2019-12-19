#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include <memory>

class Object;
class Light;

class Scene
{
private:
        float m_shadowBias;
		std::shared_ptr<std::vector<std::shared_ptr<Object>>> m_objects;
        std::shared_ptr<std::vector<std::shared_ptr<Light>>> m_lights;
public:
		Scene();
        std::shared_ptr<std::vector<std::shared_ptr<Object>>> GetObjects();
        std::shared_ptr<std::vector<std::shared_ptr<Light>>> GetLights();
};

#endif
