#include <latch>
#include <barrier>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std;

barrier go(4);

mutex m;

struct Worker {
    Worker(string name): name(name) {}
    void operator()(){
        {
            lock_guard<mutex> lg(m);
            cout << name << " arrived to the barrier... " << endl << flush;
        }
        go.arrive_and_wait();
        this_thread::sleep_for(3s);
        //go.count_down();
        //go.wait();
        {
            lock_guard<mutex> lg(m);
            cout << name << " sending a rest api call... " << endl << flush;
        }
    }
private:
    string name;
};

int main(){
    Worker worker1{"worker #1"};
    Worker worker2{"worker #2"};
    Worker worker3{"worker #3"};
    Worker worker4{"worker #4"};
    Worker worker5{"worker #5"};
    Worker worker6{"worker #6"};
    Worker worker7{"worker #7"};
    Worker worker8{"worker #8"};
    thread t1{worker1};
    this_thread::sleep_for(1s);
    thread t2{worker2};
    this_thread::sleep_for(1s);
    thread t3{worker3};
    this_thread::sleep_for(1s);
    thread t4{worker4};
    this_thread::sleep_for(1s);
    thread t5{worker5};
    this_thread::sleep_for(1s);
    thread t6{worker6};
    this_thread::sleep_for(1s);
    thread t7{worker7};
    this_thread::sleep_for(1s);
    thread t8{worker8};
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    return 0;
}