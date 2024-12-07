//
// Created by nikit on 12/7/2024.
//

#ifndef OOP_LAB_7_SRC_UTILS_SCOPEDTHREAD_H_
#define OOP_LAB_7_SRC_UTILS_SCOPEDTHREAD_H_

#include <thread>
#include "functional"
namespace Utils {

    class ScopedThread {
        std::thread thread;

        public:
            ScopedThread() = delete;
            explicit ScopedThread(const std::function<void()>& func);
            ~ScopedThread();
    };

} // Utils

#endif //OOP_LAB_7_SRC_UTILS_SCOPEDTHREAD_H_
