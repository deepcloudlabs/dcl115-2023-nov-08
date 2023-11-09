#include <iostream>
#include <thread>

using namespace std;

static int state = 0;
mutex mut;

void race() {
    cerr << "Thread ("
         << this_thread::get_id()
         <<") is running..." << endl;
    for (int i = 0; i < 1'000'000; ++i){
        { // critical section -> mutex
            lock_guard<mutex> guard(mut);
            ++state; // Divisible -> Atomic
        }
    }
}

int main() {
    thread t1(race);
    thread t2(race);
    thread t3(race);
    thread t4(race);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    std::cerr << "State: " << state << std::endl;
    return 0;
}
