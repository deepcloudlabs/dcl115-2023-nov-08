#include <iostream>
#include <stack>
#include <atomic>
#include <memory>
#include <thread>

using namespace std;

template<typename T>
class ts_stack {
    struct node {
        node* next;
        shared_ptr<T> value;
        explicit node(T value) : value(make_shared<T>(value)) {}
    };
    atomic<node*> head;
    atomic<int> counter;
public:

    void push(T value) {
        node* newNode = new node(value);
        newNode->next = head.load();
        while (!head.compare_exchange_weak(newNode->next, newNode));
        counter++;
    }

    shared_ptr<T> pop() {
        auto oldHead = head.load();
        while(oldHead && !head.compare_exchange_weak(oldHead,oldHead->next));
        return oldHead ? oldHead->value : shared_ptr<T>();
    }

    bool empty() {
        return head.load() == nullptr;
    }

    int size() {
        return counter.load();
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
