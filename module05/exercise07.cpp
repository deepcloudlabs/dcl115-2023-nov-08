#include <thread>
#include <iostream>
#include <atomic>
#include <coroutine>

using namespace std;
atomic<bool> x{false}; // Data
atomic<bool> y{false}; // Data
int data1 = 0;
int data2 = 0;

void fun1() {
    data1 = 42;
    atomic_thread_fence(memory_order_release);
    x.store(true, memory_order_release);
};

void fun2() {
    data2 = 42;
    atomic_thread_fence(memory_order_release);
    y.store(true, memory_order_release);
};

void gun1() {
    while (!y.load(memory_order_acquire));
    while (!x.load(memory_order_acquire));
    atomic_thread_fence(memory_order_acquire);
    cerr << "[gun1] data1: " << data1 << ", data2: " << data2 << endl << flush;
};

void gun2() {
    while (!x.load(memory_order_acquire));
    while (!y.load(memory_order_acquire));
    atomic_thread_fence(memory_order_acquire);
    cerr << "[gun1] data1: " << data1 << ", data2: " << data2 << endl << flush;
};

int main() {
    thread t3(gun1);
    thread t4(gun2);
    thread t1(fun1);
    thread t2(fun2);
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
    if (t3.joinable()) t3.join();
    if (t4.joinable()) t4.join();
    cout << "Application is done." << endl << flush;
    return 0;
}
