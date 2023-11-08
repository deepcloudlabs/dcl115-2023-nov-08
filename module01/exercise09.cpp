#include <iostream>
#include <thread>

using namespace std;

void task(int &id) { // call by reference
    cout << "task1 is running " << ++id << " ..." << endl;
}

int main() {
    std::cout << "Application is just started!" << std::endl;
    int state = 100; // stack -> main
    thread t1{task, ref(state)};  // stack
    thread t2(task, ref(state)); // stack
    //
    t1.join(); // synchronization point
    t2.join(); // synchronization point

    std::cout << "state: " << state << std::endl;
    std::cout << "Application is completed!" << std::endl;
    return 0;
}
