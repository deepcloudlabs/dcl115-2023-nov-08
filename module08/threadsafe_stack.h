#include <exception>
#include <stack>
#include <mutex>
#include <memory>
#include <thread>

using namespace std;

#ifndef MODULE08_THREADSAFE_STACK_H
#define MODULE08_THREADSAFE_STACK_H


template<typename T>
class threadsafe_stack {
private:
    stack<T> data;
    mutable mutex m;
public:
    threadsafe_stack();

    threadsafe_stack(const threadsafe_stack &other);

    threadsafe_stack &operator=(const threadsafe_stack &) = delete;

    void push(T new_value);

    shared_ptr<T> pop();

    void pop(T &value);

    bool empty();

    int size();
};

#endif //MODULE08_THREADSAFE_STACK_H
