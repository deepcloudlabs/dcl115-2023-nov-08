#include <iostream>
#include <thread>
#include <semaphore>

using namespace std;

binary_semaphore resource1{1};
binary_semaphore resource2{1};

void acquire() {
    while (true) {
        cerr << "Trying to acquire the first and the second resources..." << endl;
        auto ack1 = resource1.try_acquire();
        auto ack2 = resource2.try_acquire();
        if (ack1 && ack2) break;
        if (ack1) resource1.release();
        if (ack2) resource2.release();
        cerr << "Cannot acquire the first and the second resources...Sleeping 200ms..." << endl;
        this_thread::sleep_for(200ms);
    }
}

void release() {
    resource1.release();
    resource2.release();
}

void fun() {
    cerr << "fun() is just started..." << endl;
    acquire();
    cerr << "fun() has acquired the first and the second resources..." << endl;
    this_thread::sleep_for(5s);
    release();
    cerr << "fun() has released the first and the second resources..." << endl;
}

void gun() {
    cerr << "gun() is just started..." << endl;
    acquire();
    cerr << "gun() has acquired the first and the second resources..." << endl;
    this_thread::sleep_for(5s);
    release();
    cerr << "gun() has released the first and the second resources..." << endl;
}

int main() {
    cerr << "Application is just started..." << endl;
    thread t1(fun);
    thread t2(gun);
    cerr << "Threads are created..." << endl;
    t1.join();
    t2.join();
    cerr << "Application is done." << endl;
    return 0;
}