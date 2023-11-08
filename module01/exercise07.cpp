#include <iostream>
#include <thread>

using namespace std;

void task(int id) { // Text
    cerr << "task is running " << id << " ..." << endl;
    this_thread::sleep_for(10s);
    cerr << "task is now completed " << id << " ..." << endl;
}

int gun() {
    thread t1{task, 108};  // stack
    t1.detach(); //  t1.joinable() --> false
    // doing other import stuff...
    if (t1.joinable()) t1.join();
    return 42;
}

int main() {
    std::cerr << "Application is just started!" << std::endl;
    std::cerr << "Result is " << gun() << std::endl;
    this_thread::sleep_for(12s);
    std::cerr << "Application is completed!" << std::endl;
    return 0;
}
