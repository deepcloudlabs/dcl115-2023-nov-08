#include <iostream>
#include <thread>
#include <pthread.h>

using namespace std;

class thread_guard {
    std::thread &t;
public:
    explicit thread_guard(std::thread &t_) : t(t_) {}

    ~thread_guard() {
        this_thread::sleep_for(5s);
        if (t.joinable()) {
            t.join();
        }
    }

    thread_guard(thread_guard const &) = delete;

    thread_guard &operator=(thread_guard const &) = delete;
};

void task(int id) { // Text
    cout << "task is running " << id << " ..." << endl;
    std::cout << "[task] thread id: " << this_thread::get_id() << std::endl;
    pthread_t current_thread = pthread_self();
    std::cout << "[task] pthread id: " << current_thread << std::endl;
}

int main() {
    std::cout << "Application is just started!" << std::endl;
    thread t1{task, 42};  // stack
    thread t2{task, 42};  // stack
    std::cout << "[main] thread id: " << this_thread::get_id() << std::endl;
    {
        thread_guard tg1(t1);
        cout << "Now joining t1..." << endl;
    }
    {
        thread_guard tg2(t2);
        cout << "Now joining t2..." << endl;
    }
    std::cout << "Application is completed!" << std::endl;
    return 0;
}
