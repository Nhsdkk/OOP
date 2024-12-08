//
// Created by nikit on 12/8/2024.
//

#include "CoroutineHandler.h"
#include "Task.h"

Utils::Task asyncTask(const std::function<void()>& function) {
    function();
    co_await std::suspend_always{};
}

namespace Utils {
    void CoroutineHandler::await() {
        if (tasks.empty()) return;

        bool finished = false;

        while (!finished){
            for (auto& task : tasks) {
                finished = true;
                if (!task.is_done()){
                    task.resume();
                    finished = false;
                }
            }
        }
    }

    CoroutineHandler::CoroutineHandler(const std::vector<std::function<void()>> &functions) {
        for (auto& func : functions){
            tasks.push_back(asyncTask(func));
        }
    }
} // Utils