#include <iostream>
#include <thread>
#include <vector>

using namespace std;

template<typename T>
void count(int &counter, T *array, int from, int size, T value) {
    counter = 0;
    T *begin = array + from;
    T *end = begin + size;
    for (T *p = begin; p != end; ++p) {
        if (*p == value) ++counter;
    }
}

unsigned int getNumberOfLogicalProcessors() {
    return thread::hardware_concurrency();
}

template<typename T>
int parallelSolver(T *array, unsigned int size, T value) {
    vector<thread> threads;
    const unsigned int cores = getNumberOfLogicalProcessors();
    int threadLocalSize = size / cores;
    int partialCounts[cores];
    for (int i = 0, from = 0; i < cores; ++i, from += threadLocalSize) {
        threads.push_back(thread(count<T>, ref(partialCounts[i]), array, from, threadLocalSize, value));
    }
    for (thread &t: threads)
        if (t.joinable()) t.join();
    int counter = 0;
    for (int partialCount: partialCounts)
        counter += partialCount;
    return counter;
}

int main() {
    int arraySize = 120'000'000;
    int *numbers = new int[arraySize];
    for (int i = 0; i < arraySize; ++i)
        numbers[i] = i % 100;
    cout << "count: "
         << parallelSolver(numbers, arraySize, 50)
         << endl;
    delete[]numbers;
    return 0;
}
