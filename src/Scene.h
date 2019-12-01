#include <vector>
#include <memory>

class Object;

class Scene
{
private:
		std::shared_ptr<std::vector<std::shared_ptr<Object>>> m_objects;
public:
		Scene();
		std::shared_ptr<std::vector<std::shared_ptr<Object>>> getObjects();
};