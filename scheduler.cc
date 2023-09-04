#include "utils.h"


using namespace utils;

Scheduler::Scheduler() {

}

explicit Scheduler::Scheduler(int d) {
    dummy = d
}

Scheduler::~Scheduler() {

}

bool Scheduler::done() {
    for (int i; i < 6; i++) {
        if (processes[i] == nullptr)
            return false;
        else if (processes[i] -> get_state() != Finished)
            return false;
    }
    return true;
}

void Scheduler::fcfs() {
    while (1) {

        if (done())
            break;

        
    }
}

void Scheduler::sjf () {

}

void Scheduler::preemptive_priority() {

}

void Scheduler::non_preemptive_priority() {

}

void Scheduler::round_robin() {

}
