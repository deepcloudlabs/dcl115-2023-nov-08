#include <iostream>
#include <exception>
#include <stack>
#include <mutex>
#include <memory>
#include <thread>

using namespace std;

template<typename T>
class threadsafe_stack{
private:
    stack<T> data;
    mutable mutex m;
public:
    threadsafe_stack(){}
    threadsafe_stack(const threadsafe_stack& other){
        lock_guard<mutex> lock(other.m);
        data=other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value){
        lock_guard<mutex> lock(m);
        data.push(move(new_value));
    }

    shared_ptr<T> pop(){
        lock_guard<mutex> lock(m);
        if(data.empty()) return shared_ptr<T>();
        shared_ptr<T> const res(
                make_shared<T>(move(data.top())));
        data.pop();
        return res;
    }

    void pop(T& value){
        lock_guard<mutex> lock(m);
        if(data.empty()) shared_ptr<T>();
        value=move(data.top());
        data.pop();
    }

    bool empty() const {
        lock_guard<mutex> lock(m);
        return data.empty();
    }

    int size() const {
        lock_guard<mutex> lock(m);
        return data.size();
    }

};