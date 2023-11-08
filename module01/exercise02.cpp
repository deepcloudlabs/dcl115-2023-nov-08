#include <iostream>
#include <thread>

using namespace std;

struct task { // function object / functor

    explicit task(int *state) : state(state) {}

    void operator()(int id) {
        (*state)++; // Heap ? Stack
        cerr << "task is running " << id << " ..." << endl;
    }

    [[nodiscard]] int getState() const {
        return *state;
    }

private:
    int *state;
};

int main() {
    std::cerr << "Application is just started!" << std::endl;
    int value = 42; // Data ? Stack
    int *p = &value; // new int(42); // Heap
    task task1(p); // stack object
    thread t1{task1, 1};
    thread t2(task1, 2);
    thread t3(task(p), 3);
    thread t4{task(p), 4};
    t1.join(); // synchronization point
    t2.join(); // synchronization point
    t3.join(); // synchronization point
    t4.join(); // synchronization point
    std::cerr << "task1::state= " << task1.getState() << std::endl;
    std::cerr << "Application is completed!" << std::endl;
    // delete p;
    return 0;
}
