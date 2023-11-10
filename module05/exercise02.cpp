#include <thread>
#include <iostream>
#include <atomic>
#include <coroutine>

using namespace std;
atomic<int> counter{0}; // Data

void task() {
    for (auto j = 0; j < 1'000'000; ++j)
        counter++; // atomic
    cerr << "counter: " << counter.load() << endl << flush;
};

int main() {

    thread t1(task);
    thread t2(task);
    thread t3(task);
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
    if (t3.joinable()) t3.join();
    cout << "counter is " << counter.load() << endl << flush;
    cout << "Application is done." << endl << flush;
    return 0;
}
