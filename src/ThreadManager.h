/** @file ThreadManager.h
 *  @brief Class for storing threads and progress made by each thread during raytracer.
 */

#include <glm/vec2.hpp>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

class ThreadManager
{
    private:
        unsigned int m_threadsAmount; ///< Amount of CPU threads detected.
        std::vector<int> m_intervals; ///< Vector storing pixel intervals for each thread.
        std::vector<int> m_percentsDone; ///< Vector storing percentage progress of each thread.
    public:
        /** @brief Initializes the manager by detecting the amount of CPU threads and calculating the intervals from window size.
         *  @param _windowSize The dimensions of the window.
         */
        bool Init(glm::ivec2 _windowSize);
        /// @brief Returns the amount of threads.
        unsigned int GetThreadsAmount();
        /// @brief Returns a vector storing pixel intervals for each thread.
        std::vector<int> GetIntervals();
        /** @brief Returns the progress made by the specified thread.
         *  @param _threadId Thread ID number, used for displaying its progress.
         */
        int GetPercentDone(int _threadId);
        /** @brief Sets the progress made by the specified thread.
         *  @param _threadId Thread ID number, used for displaying its progress.
         *  @param _percentDone The percentage of the progress made by a thread.
         */
        void SetPercentDone(int _threadId, int _percentDone);
        /** A vector of threads. Has to be public, as returning them by
         *  using a getter returns an exception. */
        std::vector<std::thread> m_threads;
};
