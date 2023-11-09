#include <thread>
#include <iostream>
#include <mutex>
#include <future>
#include <functional>

using namespace std;


int main() {
    cout << "Application is just started." << endl << flush;
    promise<int> provider;
    future<int> consumer = provider.get_future();
    thread([&provider]() {
        this_thread::sleep_for(5s);
        cout << "Producer setting value to 42." << endl << flush;
        provider.set_value(42);
    }).detach();
    consumer.wait();
    cout << "Consumer: " << consumer.get() << endl << flush;
    cout << "Application is just completed." << endl << flush;
    return 0;
}