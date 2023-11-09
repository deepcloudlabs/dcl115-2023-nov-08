#include <memory>
#include <mutex>
#include <thread>

using namespace std;

class precious_resource { // ts
public:
    void do_business(){}
};

shared_ptr<precious_resource> resource_ptr;
once_flag resource_flag;

void init_resource(){
   resource_ptr.reset(new precious_resource());
}

void fun(){
    call_once(resource_flag,init_resource);
    resource_ptr->do_business();
}

int main(){
    thread t1(fun);
    thread t2(fun);
    t1.join();
    t2.join();
    return 0;
}