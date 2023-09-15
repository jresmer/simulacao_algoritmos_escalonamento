#include "utils.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace utils;

int main()
{
    CPU cpu = CPU();
    Kernel kernel = Kernel(FCFS);

    cpu.set_so(kernel);
    cpu.run();
    kernel.reset();

    kernel.set_algorithm(SJF);
    cpu.set_so(kernel);
    cpu.run();
    kernel.reset();

    kernel.set_algorithm(NONPREEMPTIVEPRIO);
    cpu.set_so(kernel);
    cpu.run();
    kernel.reset();

    kernel.set_algorithm(PREEMPTIVEPRIO);
    cpu.set_so(kernel);
    cpu.run();
    kernel.reset();

    kernel.set_algorithm(ROUNDROBIN);
    cpu.set_so(kernel);
    cpu.run();

}
