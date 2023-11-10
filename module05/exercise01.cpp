#include <thread>
#include <iostream>

using namespace std;

struct task { // functor
    int &data; // shared memory
    task(int &data) : data(data) {}

    void operator()() {
        for (auto j = 0; j < 1'000'000; ++j)
            data++; // race
        cerr << "data: " << data << endl << flush ;
    }
};

int main() {
    int local_data = 0;
    task task1(local_data);
    thread t1(task1);
    thread t2(task1);
    thread t3(task1);
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
    if (t3.joinable()) t3.join();
    cout << "local data is " << local_data << endl << flush;
    cout << "Application is done." << endl << flush;
    return 0;
}
