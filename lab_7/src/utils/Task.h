//
// Created by nikit on 12/8/2024.
//

#ifndef OOP_LAB_7_SRC_UTILS_TASK_H_
#define OOP_LAB_7_SRC_UTILS_TASK_H_

#include <coroutine>
#include <exception>
namespace Utils {

struct Task {
    struct promise_type {
        bool finished = false;

        Task get_return_object() { return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept {
            finished = true;
            return {};
        }

        void return_void() {}

        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> coro;

    explicit Task(std::coroutine_handle<promise_type> coro) : coro(coro) {}

    Task(Task&& other) noexcept : coro(other.coro) { other.coro = nullptr; }

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    bool is_done() const {
        return coro.promise().finished;
    }

    void resume() const {
        if (!is_done()) coro.resume();
    }

    ~Task() { if (coro) coro.destroy(); }
};

} // Utils

#endif //OOP_LAB_7_SRC_UTILS_TASK_H_
