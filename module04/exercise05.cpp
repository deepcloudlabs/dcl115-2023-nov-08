#include <thread>
#include <iostream>
#include <mutex>
#include <future>

using namespace std;


int main() {
    // js: promise, async/await, generator: yield
    // function fun(){ return new Promise((resolve,reject) => { setTimeout( () => { resolve(42); }, 5000)});  }
    // fun().then( number => console.log(number) )
    // async function fun(){ return 42;  }
    // python: async, await, generator: yield
    // async def fun() -> int : return 42
    // promise -> CompletableFuture
    // c++: <coroutine>: async/await, generator: co_yield, co_await
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