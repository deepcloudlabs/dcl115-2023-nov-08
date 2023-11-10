#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>
#include <functional>

#include "threadsafe_queue.cpp"

using namespace std;

class join_threads {
    vector<thread> &threads;
public:
    explicit join_threads(vector<thread> &threads_) : threads(threads_) {}

    ~join_threads() {
        for (auto &thread: threads) {
            if (thread.joinable())
                thread.join();
        }
    }
};

class thread_pool {
    atomic_bool done;
    thread_safe_queue<function<void()>> work_queue;
    vector<thread> threads;
    join_threads joiner;
    unsigned thread_count = thread::hardware_concurrency();

    void worker_thread() {
        while (!done) {
            function<void()> task;
            if (work_queue.try_pop(task)) {
                task();
            } else {
                this_thread::sleep_for(50ms);
            }
        }
    }

public:
    thread_pool() : joiner(threads), done(false) {
        try {
            for (int i = 0; i < thread_count; ++i) {
                threads.emplace_back(&thread_pool::worker_thread, this);
            }
        }
        catch (...) {
            done = true;
            throw;             // re-throw
        }
    }

    ~thread_pool() {
        done = true;
    }

    template<typename FunctionType>
    void submit(FunctionType f) {
        work_queue.push(function<void()>(f));
    }
};

void fun() {
    cout << "Hello Mars!" << endl;
}


void gun() {
    cout << "Hello Moon!" << endl;
}


int main() {
    thread_pool my_pool;
    for (int i = 0; i < 5'000; ++i) {
        my_pool.submit(function<void()>(fun));
        my_pool.submit(function<void()>(gun));
        this_thread::sleep_for(1us);
    }


    this_thread::sleep_for(60s);
}
