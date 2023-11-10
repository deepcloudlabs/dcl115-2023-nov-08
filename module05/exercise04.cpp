#include <thread>
#include <iostream>
#include <atomic>
#include <coroutine>

using namespace std;
atomic<bool> flag{false}; // Data
int a = 0;

void fun() {
    a = 42;
    atomic_thread_fence(memory_order_release);
    flag.store(true, memory_order_relaxed);
};

void gun() {
    while (!flag.load(memory_order_relaxed));
    atomic_thread_fence(memory_order_acquire);
    cerr << "a is " << a << endl << flush; // guarantied to print 42
};

int main() {

    thread t1(fun);
    thread t2(gun);
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
    cout << "Application is done." << endl << flush;
    return 0;
}
