#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

using namespace std;
struct A{
    A(){ cerr << "Thread with id " << this_thread::get_id() << "=> A(), " << hex << this << endl; }
    ~A(){ cerr << "Thread with id " << this_thread::get_id() << "=> ~A(), " << hex << this<< endl; }
    void sun(){}
};
thread_local int state = 0; // static: Data -> thread_local: Thread's Stack
thread_local A a; // Data -> Thread's Stack

mutex m;

void fun() {
    ++state;
    a.sun();
    lock_guard<mutex> lg(m);
    cerr << "[fun] Thread with id " << this_thread::get_id()
         << ", "
         << state
         << ", "
         << hex << &state
         << endl;
}

void gun() {
    ++state;
    lock_guard<mutex> lg(m);
    cerr << "[gun] Thread with id " << this_thread::get_id()
         << ", "
         << state
         << ", "
         << hex << &state
         << endl;
}

int main() {
    thread t1([]() {
        fun();
        gun();
    });
    thread t2([]() {
        fun();
        gun();
    });
    thread t3([]() {
        fun();
        gun();
    });
    thread t4([]() {
        fun();
        gun();
    });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cout << "state: " << state << endl;
    return 0;
}