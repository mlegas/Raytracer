#include "ThreadManager.h"

bool ThreadManager::Init(glm::ivec2 _windowSize)
{
    m_threadsAmount = std::thread::hardware_concurrency();

    if (m_threadsAmount == 0)
    {
        // assume at least 2 cores if unable to detect
        // most likely C++11 is not supported or CPU information is impossible to be obtained
        m_threadsAmount = 2;
        // return -1;
        // change above lines if safety & reliability is more important
    }

    m_threadsAmount = 1;

    int xInterval = _windowSize.x / m_threadsAmount;
    int xRemainder = _windowSize.x % m_threadsAmount;

    for (int i = 0, sum = 0; i < m_threadsAmount; i++)
    {
        sum += xInterval;
        m_intervals.push_back(sum);
    }

    if (xRemainder > 0)
    {
        for (int x = 0; x < xRemainder; x++)
        {
            m_intervals.at(x) += 1;
        }
    }

    return true;
}
