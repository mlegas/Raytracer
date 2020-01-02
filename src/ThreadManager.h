#include <memory>
#include <thread>
#include <mutex>
#include <vector>
#include <glm/vec2.hpp>

class ThreadManager
{
private:
    unsigned int m_threadsAmount;
    std::vector<int> m_intervals;
    std::vector<int> m_percentsDone;
public:
    bool Init(glm::ivec2 _windowSize);
    unsigned int GetThreadsAmount();
    std::vector<int> GetIntervals();
    int GetPercentDone(int _threadId);
    void SetPercentDone(int _threadId, int _percentDone);
    std::vector<std::thread> m_threads;
};
