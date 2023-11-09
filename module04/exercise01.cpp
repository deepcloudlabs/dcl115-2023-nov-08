#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

static bool flag = false;
mutex mut;

void wait_for(){
    unique_lock<mutex> ul(mut);
    while(!flag){
        ul.unlock();
        this_thread::sleep_for(100ms);
        ul.lock();
    }
}

void fun(){
    cerr << "fun starts now..." << endl;
    cerr << "I have arrived rendezvous point." << endl;
    wait_for();
    cerr << "Let us have fun now..." << endl;
}

void gun(){
    cerr << "gun starts now..." << endl;
    this_thread::sleep_for(10s);
    cerr << "I have arrived rendezvous point." << endl;
    flag = true;
    cerr << "Let us have gun now..." << endl;
}

int main() {
    cerr << "Application is just started." << endl;
    thread t1(fun);
    thread t2(gun);
    t1.join();
    t2.join();
    cerr << "Application is done." << endl;
    return 0;
}
