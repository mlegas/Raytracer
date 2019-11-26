class Scene
{
private:
		std::vector<std::shared_ptr<Object>> m_objects;
public:
		Scene();
		std::vector<std::shared_ptr<Object>> getObjects();
};
