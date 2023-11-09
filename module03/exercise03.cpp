#include <memory>
#include <mutex>
#include <thread>

using namespace std;

class precious_resource { // ts
public:
    void do_business(){}
};

shared_ptr<precious_resource> resource_ptr;
mutex resource_mutex;

void fun(){
    { // atomic -> lazy initialization
        unique_lock<mutex> ul(resource_mutex);
        if(!resource_ptr)
            resource_ptr.reset(new precious_resource());
    }
    resource_ptr->do_business();
}

int main(){
    thread t1(fun);
    thread t2(fun);
    t1.join();
    t2.join();
    return 0;
}