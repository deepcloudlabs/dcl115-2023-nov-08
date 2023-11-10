#include <iostream>
#include <stack>
#include <mutex>
#include <memory>
#include <thread>

using namespace std;

template<typename T>
class ts_stack {
    stack<T> container;
    mutex m;
public:
    ts_stack() = default;

    ts_stack(const ts_stack &other) {
        lock_guard<mutex> lock(other.m);
        container = other.container;
    }

    void push(T value) {
        lock_guard<mutex> lock(this->m);
        container.push(move(value));
    }

    shared_ptr<T> pop() {
        lock_guard<mutex> lock(this->m);
        auto top = container.top();
        container.pop();
        return make_shared<T>(std::move(top));
    }

    bool empty() {
        lock_guard<mutex> lock(this->m);
        return container.empty();
    }

    int size() {
        lock_guard<mutex> lock(this->m);
        return container.size();
    }
};

ts_stack<int> my_numbers;

void fun(int start, int count) {
    for (int i = start, j = 0; j < count; ++i, ++j) {
        my_numbers.push(i);
    }
}

int main() {
    thread t1(fun,0,1'000'000);
    thread t2(fun,1'000'000,1'000'000);
    thread t3(fun,2'000'000,1'000'000);
    thread t4(fun,3'000'000,1'000'000);
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
    if (t3.joinable()) t3.join();
    if (t4.joinable()) t4.join();
    cout << my_numbers.size() << endl;
    return 0;
}
