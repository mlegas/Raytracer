#include <vector>
#include <memory>

class Object;
class Light;

class Scene
{
private:
		std::shared_ptr<std::vector<std::shared_ptr<Object>>> m_objects;
        std::shared_ptr<std::vector<std::shared_ptr<Light>>> m_lights;
public:
		Scene();
		std::shared_ptr<std::vector<std::shared_ptr<Object>>> getObjects();
        std::shared_ptr<std::vector<std::shared_ptr<Light>>> getLights();
};
