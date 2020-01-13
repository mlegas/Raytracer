/** @file Scene.h
 *  @brief Class responsible for constructing and storing objects and lights to be displayed.
 */

#include <memory>
#include <vector>

class Object;
class Light;

class Scene
{
    private:
        int m_maxDepth; ///< Maximum depth limit for reflecton and transmission rays.
        std::shared_ptr<std::vector<std::shared_ptr<Object>>> m_objects; ///< Stores all objects in the scene.
        std::shared_ptr<std::vector<std::shared_ptr<Light>>> m_lights; ///< Stores all lights in the scene.
    public:
        /** @brief Constructs the scene, initializing all objects and lights.
         *  @param _maxDepth The depth limit for reflection and transmission rays.
         */
        Scene(int _maxDepth);
        /// @brief Returns a vector with all objects in the scene.
        std::shared_ptr<std::vector<std::shared_ptr<Object>>> GetObjects();
        /// @brief Returns a vector with all lights in the scene.
        std::shared_ptr<std::vector<std::shared_ptr<Light>>> GetLights();
        /// @brief Returns the maximum depth limit for reflection and transmission rays.
        int GetMaxDepth();
};
