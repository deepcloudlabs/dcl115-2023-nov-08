#include <iostream>
#include <thread>
#include <numeric>

using namespace std;

void gun() {
    cout << "gun() is running..." << endl;
    this_thread::sleep_for(1s);
}

void fun(thread t) {
    cout << "fun() is running..." << endl;
    // if (t.joinable()) t.join();
    t.detach();
}

int main() {
    cout << "Application is just started..." << endl;
    thread t1(gun);
    fun(std::move(t1));
    //if (t1.joinable()) t1.join(); // no longer need to join
    cout << "Application is completed..." << endl;
    return 0;
}
