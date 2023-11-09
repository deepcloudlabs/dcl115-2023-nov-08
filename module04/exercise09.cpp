#include <iostream>
#include <thread>
#include <semaphore>

using namespace std;

binary_semaphore resource1{1};
binary_semaphore resource2{1};

void fun() {
    cerr << "fun() is just started..." << endl;
    resource1.acquire();
    cerr << "fun() has acquired the first resource..." << endl;
    this_thread::sleep_for(2s);
    resource2.acquire();
    cerr << "fun() has acquired the second resource..." << endl;
    resource1.release();
    cerr << "fun() has released the first resource..." << endl;
    resource2.release();
    cerr << "fun() has released the second resource..." << endl;
}

void gun() {
    cerr << "gun() is just started..." << endl;
    resource2.acquire();
    cerr << "gun() has acquired the second resource..." << endl;
    this_thread::sleep_for(2s);
    resource1.acquire();
    cerr << "gun() has acquired the first resource..." << endl;
    resource1.release();
    cerr << "gun() has released the first resource..." << endl;
    resource2.release();
    cerr << "fun() has released the second resource..." << endl;
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