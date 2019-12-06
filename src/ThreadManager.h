#include <memory>
#include <thread>
#include <mutex>
#include <vector>
#include <glm/vec2.hpp>

struct ThreadManager
{
    unsigned int m_threadsAmount;
    std::vector<int> m_intervals;
    std::vector<std::thread> m_threads;
    std::mutex m_mtx;
    bool init(glm::ivec2 _windowSize);
};
