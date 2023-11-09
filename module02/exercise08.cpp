#include <thread>
#include <iostream>
#include <functional>

using namespace std;

void taskA(int x, int y) {
    cerr << "Running a task: x= " << x << ", y= " << y << endl;
}

void taskB(const int *array, int length) {
    for (auto i = 0; i < length; ++i)
        cerr << "array[" << i << "]: " << array[i] << endl;
}

void taskC(int &sum, const int *array, int length) {
    sum = 0;
    for (auto i = 0; i < length; ++i)
        sum += array[i];
}

void taskD(const int &sum, [[maybe_unused]] const int *array, [[maybe_unused]] int length) {
    cerr << "sum: " << sum << endl;
}

int main() {
    int a = 42, b = 108, total = 0;
    int dizi[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cerr << "Application is just started..." << endl;
    thread t1(taskA, a, b);
    thread t2(taskB, dizi, 10);
    thread t3(taskC, ref(total), dizi, 10);
    thread t4(taskD, cref(total), dizi, 10);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cerr << "Application is done: " << total << endl;
    return 0;
}