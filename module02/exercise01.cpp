#include <iostream>
#include <thread>

using namespace std;

void task(int id) { // Text
    cout << "task is running " << id << " ..." << endl;
    std::cout << "[task] thread id: " << this_thread::get_id() << std::endl;
}

int main() {
    std::cout << "Application is just started!" << std::endl;
    thread t1{task, 42};  // stack
    std::cout << "[main] thread id: " << this_thread::get_id() << std::endl;
    if (t1.joinable()) t1.join();
    return 0;
}
