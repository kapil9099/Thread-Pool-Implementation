#include <iostream>
#include <vector>
#include <mutex>
#include "ThreadPool.h"

int main() {
    ThreadPool pool(4);  // Create a thread pool with 4 threads
    std::vector<std::future<int>> results;
    std::mutex cout_mutex;  // Mutex to synchronize console output

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i, &cout_mutex] {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);  // Lock mutex
                    std::cout << "Task " << i << " is executing" << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate work
                return i * i;
            })
        );
    }

    for (auto && result : results) {
        int value = result.get();  // Ensure the result is fetched outside the mutex lock
        {
            std::lock_guard<std::mutex> lock(cout_mutex);  // Lock mutex for result output
            std::cout << "Result: " << value << std::endl;
        }
    }

    return 0;
}

