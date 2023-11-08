#include <iostream>
#include <thread>

using namespace std;
int state = 100; // Data --> Process

void task1(int id) { // Text
    [[maybe_unused]] static int local = 0; // stack -- with static --> Data (Process)
    // id, local variables live inside thread's stack
    cout << "task1 is running " << id << " ..." << endl;
    state++;  // race
}

int main() {
    std::cout << "Application is just started!" << std::endl;
    thread t1{task1, 42};  // stack
    thread t2(task1, 258); // stack
    //
    t1.join(); // synchronization point
    t2.join(); // synchronization point

    std::cout << "state: " << state << std::endl;
    std::cout << "Application is completed!" << std::endl;
    return 0;
}
