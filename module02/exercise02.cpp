#include <iostream>
#include <thread>
#include <pthread.h>

using namespace std;

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
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
    return 0;
}
