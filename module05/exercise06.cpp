#include <thread>
#include <iostream>
#include <atomic>
#include <coroutine>

using namespace std;
atomic<bool> x{false}; // Data
atomic<bool> y{false}; // Data

void fun1() {
    x.store(true, memory_order_release);
};

void fun2() {
    while (!x.load(memory_order_acquire));
    y.store(true, memory_order_release);
};

void gun() {
    while (!y.load(memory_order_acquire));
    if (x.load(memory_order_acquire)) {
        cerr << "x and y are both true." << endl << flush;
    } else {
        cerr << "y is true and x is false." << endl << flush;
    }
};

int main() {

    thread t2(fun2);
    thread t3(gun);
    thread t1(fun1);
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
    if (t3.joinable()) t3.join();
    cout << "Application is done." << endl << flush;
    return 0;
}
