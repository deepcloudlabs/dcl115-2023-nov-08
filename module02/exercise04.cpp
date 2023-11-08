#include <iostream>
#include <thread>

using namespace std;

void task1(int *p) { // Text
    for (auto i = 0; i < 10; ++i) {
        cout << "task is running " << i << " using state " << *p << endl;
        (*p)++;
        this_thread::sleep_for(1s);
    }

}

void task2(int &p) { // Text
    for (auto i = 0; i < 10; ++i) {
        cout << "task is running " << i << " using state " << p << endl;
        p++;
        this_thread::sleep_for(1s);
    }

}

void fun() { // text -> process
    int state[5] = {42, 42, 42, 42, 42}; // stack -> main
    thread t1{task1, state + 4};  // error: stack
    thread t2{task2, ref(state[4])};  // error: stack
    t1.detach();
    t2.detach();
    this_thread::sleep_for(3s);
}

void gun() {
    [[maybe_unused]]
    int number[4]{100, 200, 300, 400};
}

int main() {
    fun();
    gun();
    std::cout << "Application is just started!" << std::endl;
    this_thread::sleep_for(5s);
    std::cout << "Application is completed!" << std::endl;
    return 0;
}
