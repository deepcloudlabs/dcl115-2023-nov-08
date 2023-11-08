#include <iostream>
#include <thread>

using namespace std;

void task(int id) { // Text
    cout << "task is running " << id << " ..." << endl;
}

int main() {
    std::cout << "Application is just started!" << std::endl;
    thread t1{task, 42};  // stack
    t1.detach(); // no longer required to join
    {
        jthread t2{task, 108};  // stack
        //t2.detach(); // t2.joinable() -> false
        // not required for jthread: if(t2.joinable()) t2.join();
    } // End of scope -> t2 -> if (t2.joinable()) t2.join()
    std::cout << (t1.joinable() ? "true" : "false") << std::endl;
/*
    if (t1.joinable())
        t1.join();
*/
    std::cout << "Application is completed!" << std::endl;
    return 0;
}
