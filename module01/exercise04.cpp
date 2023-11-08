#include <iostream>
#include <thread>

using namespace std;

class Task {
    int state;
public:
    explicit Task(int state) : state(state) {}

    void fun(int id) { // Text
        this->state++;
        cout << "fun is running " << id << " ..." << endl;
    }

    [[nodiscard]] int getState() const {
        return state;
    }
};

int main() {
    std::cerr << "Application is just started!" << std::endl;
    Task task1(1); // Stack
    Task task2(2); // Stack
    Task task3(3); // Stack
    thread t1{&Task::fun, &task1, 42};
    thread t2{&Task::fun, &task1, 42};
    thread t3{&Task::fun, &task2, 108};
    thread t4{&Task::fun, &task3, 3615};
    t1.join(); // synchronization point
    t2.join(); // synchronization point
    t3.join(); // synchronization point
    t4.join(); // synchronization point
    std::cerr << "state: " << task1.getState() << std::endl;
    std::cerr << "Application is completed!" << std::endl;
    return 0;
}
