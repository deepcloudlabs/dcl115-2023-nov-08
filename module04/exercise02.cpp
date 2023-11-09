#include <thread>
#include <queue>
#include <list>
#include <mutex>
#include <condition_variable>
#include <iostream>

using namespace std;

struct product{};

struct purchase_order {};

mutex m;
queue<purchase_order> orders;

condition_variable order_ready;

void receive_po(list<purchase_order>& new_orders){
    while(true){
        cerr << "receive_po: received new orders..." << endl;
        for(auto &order: new_orders){
            lock_guard<mutex> lg(m);
            orders.push(order);
            cerr << "receive_po: adding orders to the queue...notifying the consumer!" << endl;
            order_ready.notify_one();
        }
        this_thread::sleep_for(5s);
    }
}

void process_po(){
    while(true){
        unique_lock<mutex> ul(m);
        cerr << "process_po: waiting for orders..." << endl;
        order_ready.wait(ul, []{return !orders.empty();});
        cerr << "process_po: received new po..." << endl;
        purchase_order po = orders.front();
        orders.pop();
        ul.unlock();
        cerr << "process_po: processing the po ..." << endl;
        this_thread::sleep_for(100ms);
    }
}


int main(){
    cerr << "Application is just started." << endl;
    list<purchase_order> orders{
            purchase_order{},
            purchase_order{},
            purchase_order{},
            purchase_order{}
    };
    thread producer1(receive_po,ref(orders));
    thread producer2(receive_po,ref(orders));
    thread consumer1(process_po);
    thread consumer2(process_po);
    thread consumer3(process_po);
    thread consumer4(process_po);
    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
    cerr << "Application is done." << endl;
    return 0;
}