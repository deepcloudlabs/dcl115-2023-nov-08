#include <thread>
#include <iostream>
#include <atomic>
#include <coroutine>

using namespace std;
atomic<bool> x{0}; // Data
atomic<bool> y{0}; // Data

void fun() {
    x.store(true,memory_order_seq_cst);
    y.store(true,memory_order_seq_cst);
};
void gun() {
    while (!y.load(memory_order_seq_cst));
    if (x.load(memory_order_seq_cst)){
        cerr << "x and y are both true" << endl << flush;
    }
};

int main() {

    thread t1(fun);
    thread t2(gun);
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
    cout << "Application is done." << endl << flush;
    return 0;
}
