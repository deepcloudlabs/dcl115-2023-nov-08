#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
class vehicle { // ts
    const double capacity;
    double currentLoad;

public:
    mutex m;
    explicit vehicle(const double capacity) : capacity(capacity) {
        this->currentLoad = 0.0;
    }

    const double getCapacity() const {
        return capacity;
    }

    double getCurrentLoad() {
        lock_guard<mutex> guard(m);
        return currentLoad;
    }

    double load(double weight) {
        //lock_guard<mutex> guard(m);
        if (weight <= 0) return this->currentLoad;
        if ((weight + this->currentLoad > this->capacity))
            return this->currentLoad;
        this->currentLoad += weight;
        return this->currentLoad;
    }

    double unload(double weight) {
        //lock_guard<mutex> guard(m);
        if (weight <= 0) return this->currentLoad;
        if (weight > this->currentLoad)
            return this->currentLoad;
        this->currentLoad -= weight;
        return this->currentLoad;
    }
};

void transferLoad(vehicle& from,vehicle& to,double weight){
    unique_lock<mutex> lock1{from.m,defer_lock};
    unique_lock<mutex> lock2{to.m,defer_lock};
    lock(lock1,lock2);
    from.unload(weight);
    to.load(weight);
}


void task(vehicle& vehicle1,vehicle& vehicle2){
    for (int i=0;i<10;++i){
        vehicle1.load(200);
        vehicle2.load(200);
    }
    for (int i=0;i<10;++i) {
        transferLoad(vehicle1, vehicle2, 50);
    }
}
int main() {
    vehicle v1(10'000);
    vehicle v2(5'000);
    thread t1(task,ref(v1),ref(v2));
    thread t2(task,ref(v1),ref(v2));
    t1.join();
    t2.join();
    return 0;
}
