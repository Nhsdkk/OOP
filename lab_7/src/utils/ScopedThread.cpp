//
// Created by nikit on 12/7/2024.
//

#include "ScopedThread.h"

namespace Utils {
    ScopedThread::ScopedThread(const std::function<void()>& func) {
        std::thread t(func);
        if (!t.joinable()) throw std::logic_error("Can't join thread");
        thread = std::move(t);
    }

    ScopedThread::~ScopedThread() {
        if (thread.joinable()) thread.join();
    }
} // Utils