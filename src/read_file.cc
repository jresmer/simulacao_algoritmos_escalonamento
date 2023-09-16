#include "utils.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace utils;

int main()
{
    CPU cpu = CPU();
    Kernel kernel = Kernel(PREEMPTIVEPRIO);

    cpu.set_so(kernel);
    cpu.run();
}
