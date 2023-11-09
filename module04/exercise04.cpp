#include <thread>
#include <iostream>
#include <mutex>
#include <future>
#include <functional>

using namespace std;
// 7 -> 22 -> 11 -> 34 -> 17 -> 52 -> 26 -> 13 -> 40 -> 20
// 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
long fun(long n) {
    cerr << "[fun]" << this_thread::get_id() << endl;
    long step = 0;
    while (n > 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        step++;
        this_thread::sleep_for(500ms);
    }
    return step;
}

int main(){
    cerr << "Application is just started." << endl;
    future<long> result = async(std::launch::async,fun,7); // 16 ?
    cerr << "[main]" << this_thread::get_id() << endl;
    cerr << result.get() << endl;
    auto fun7 = bind(fun,7);
    packaged_task<long()> task(fun7);
    task();
    cerr << task.get_future().get() << endl;

    cerr << "Application is just completed." << endl;
    return 0;
}