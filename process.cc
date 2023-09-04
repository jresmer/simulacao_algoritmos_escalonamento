#include "utils.h"


using namespace utils;

Process::Process(int ct, int d, int p) {
    creation_time = ct;
    duration = d;
    priority = p;
    executed_time = d;
    state = New;
}

Process::~Process() {

}

void Process::set_turnaround(int tt) {
    turnaround_time = tt;
}

void Process::set_wait_time(int wt) {
    wait_time = wt;
}

void Process::func(int d) { // incompleto??
    state = Executing;
    executed_time++;
    sleep(1); // dormir 1 seg
    if (executed_time == duration) {
        state = Finished;
    }
}

void Process::set_state_ready() {
    state = Ready;
}

State Process::get_state() {
    return state;
}


