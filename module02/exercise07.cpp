#include <thread>
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

void task(int task_id) {
    cerr << endl
         << "Running task #" << task_id
         << ", executed by the thread #" << this_thread::get_id()
         << endl << flush;
}

void fun() {
    vector<thread> threads;
    cerr << endl << "Creating threads..." << endl << flush;
    for (auto i = 1; i <= 50; i++)
        threads.emplace_back((thread(task, i)));

    cerr << endl << "Joining threads..." << endl;
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    cerr << endl << "Leaving fun()..." << endl << flush;
}

int main() {
    cerr << endl << "Application is just started..." << endl << flush;
    fun();
    cerr << endl << "Application is done." << endl << flush;
    return 0;
}