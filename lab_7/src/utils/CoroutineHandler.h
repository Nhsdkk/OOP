//
// Created by nikit on 12/8/2024.
//

#ifndef OOP_LAB_7_SRC_UTILS_COROUTINEHANDLER_H_
#define OOP_LAB_7_SRC_UTILS_COROUTINEHANDLER_H_

#include <functional>
#include "Task.h"
namespace Utils {

    class CoroutineHandler {
        std::vector<Utils::Task> tasks;

        public:
            CoroutineHandler() : tasks() {}
            explicit CoroutineHandler(const std::vector<std::function<void()>>& functions);
            void await();
            ~CoroutineHandler() = default;
    };

} // Utils

#endif //OOP_LAB_7_SRC_UTILS_COROUTINEHANDLER_H_
