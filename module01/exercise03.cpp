#include <iostream>
#include <thread>

using namespace std;

struct [[maybe_unused]] anonymous {
    int state;

    void operator()(int id) {
        state++;
        cout << "lambda task1 is running " << id << " ..." << endl;
    }
};

int main() {
    std::cerr << "Application is just started!" << std::endl;
    int state = 100;
    thread t1{[&state](int id) {
        state++;
        cout << "lambda task1 is running " << id << " ..." << endl;
    }, 1};
    thread t2{[&](int id) {
        state++;
        cout << "lambda task2 is running " << id << " ..." << endl;
    }, 2};
    thread t3{[&](int id) {
        state++;
        cout << "lambda task3 is running " << id << " ..." << endl;
    }, 3};
    t1.join(); // synchronization point
    t2.join(); // synchronization point
    t3.join(); // synchronization point
    std::cerr << "state: " << state << std::endl;
    std::cerr << "Application is completed!" << std::endl;
    return 0;
}
