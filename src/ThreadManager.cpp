/** @file ThreadManager.cpp
 *  @brief Implementation of functions for the ThreadManager class.
 */

#include "ThreadManager.h"

bool ThreadManager::Init(glm::ivec2 _windowSize)
{
    m_threadsAmount = 0;
    /// Receive the amount of available CPU threads using C++11.
    m_threadsAmount = std::thread::hardware_concurrency();

    if (m_threadsAmount == 0)
    {
        /// Most likely C++11 is not supported or CPU information is impossible to be obtained, return.
        return -1;
    }
    /// Uncomment this line to use only a single thread.
    //m_threadsAmount = 1;

    /** Divides the width of the window by the amount of threads,
     *  obtaining how large is an interval. */
    int xInterval = _windowSize.x / m_threadsAmount;
    /// Store the remainder of the division.
    int xRemainder = _windowSize.x % m_threadsAmount;

    for (int i = 0, sum = 0; i < m_threadsAmount; i++)
    {
        /// Creates the set pixel intervals by adding the calculated interval amount.
        sum += xInterval;
        m_intervals.push_back(sum);
    }

    if (xRemainder > 0)
    {
        for (int x = 0; x < xRemainder; x++)
        {
            /** As the remainder of the division will never be higher
             *  than the amount of CPU threads available, we can safely add
             *  a small part of the remainder to each interval. This might sometimes leave
             *  a few threads having one pixel less to ray trace than the others. */
            m_intervals.at(x) += 1;
        }
    }
    /// Initialize the progress vector with zeros.
    m_percentsDone = std::vector<int>(m_threadsAmount, 0);

    /// Initialize the progress check vector with false boolean values.
    m_showProgress = std::vector<bool>(m_threadsAmount, false);

    return true;
}

unsigned int ThreadManager::GetThreadsAmount()
{
    return m_threadsAmount;
}

std::vector<int> ThreadManager::GetIntervals()
{
    return m_intervals;
}

int ThreadManager::GetPercentDone(int _threadId)
{
    return m_percentsDone.at(_threadId);
}

void ThreadManager::SetPercentDone(int _threadId, int _percentDone)
{
    m_percentsDone.at(_threadId) = _percentDone;
}

bool ThreadManager::IsShowingProgress(int _threadId)
{
    return m_showProgress.at(_threadId);
}

void ThreadManager::SetShowingProgress(int _threadId, bool _isShowing)
{
    m_showProgress.at(_threadId) = _isShowing;
}

