#include <iostream>
#include <thread>

using namespace std;

int main() {
    std::cerr << "Application is just started!" << std::endl;
    std::cerr << "# of logical processors: " << thread::hardware_concurrency() << std::endl;
    std::cerr << "Application is completed!" << std::endl;
    return 0;
}
