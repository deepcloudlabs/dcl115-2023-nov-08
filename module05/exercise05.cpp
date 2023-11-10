#include <thread>
#include <iostream>
#include <atomic>
#include <coroutine>

using namespace std;
atomic<int> counter{0}; // Data
int a = 0;

void fun() {
    for (int i = 0; i < 1'000'000; ++i) {
        a = i;
        atomic_thread_fence(memory_order_release);
        counter.store(i, memory_order_relaxed);
    }
};

void gun() {
    int previousValue = 0;
    while (previousValue < 1'000'000) {
        while (true) {
            int newValue = counter.load(memory_order_relaxed);
            // cout << "newValue " << newValue << " , previousValue: " << previousValue << endl << flush;
            if (previousValue < newValue) {
                previousValue = newValue;
                atomic_thread_fence(memory_order_acquire);
                cout << "a: " << a << " , previousValue: " << previousValue << endl << flush;
                break;
            }
        }
    }
    //atomic_thread_fence(memory_order_acquire);
};

int main() {

    thread t1(fun);
    thread t2(gun);
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
    cout << "Application is done." << endl << flush;
    return 0;
}
