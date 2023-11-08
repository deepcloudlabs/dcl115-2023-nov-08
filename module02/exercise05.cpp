#include <iostream>
#include <thread>
#include <numeric>

using namespace std;


void m(int &result, int *begin, int *end) {
    result = accumulate(begin, end, int(),
                        [](int acc, int val) {
                            return acc + val;
                        });
}

int main() {
    int lost[] = {4, 8, 15, 16, 23, 42}, sum;
    thread t(m, ref(sum), lost, lost + 6);
    t.join();
    cout << "sum is " << sum << endl;
    return 0;
}
