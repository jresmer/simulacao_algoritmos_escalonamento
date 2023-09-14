#include "utils.h"

using namespace utils;
using namespace std;

Process::Process() = default;

Process::Process(int ct, int d, int p, int id) {
    pid = id;
    creation_time = ct;
    duration = d;
    priority = p;
    executed_time = 0;
    turnaround_time = 0;
    wait_time = 0;
    state = New;
}

Process::~Process() = default;

void Process::set_turnaround(int tt) {
    turnaround_time = tt;
}

void Process::set_wait_time(int wt) {
    wait_time = wt;
}

void Process::executed() {
    state = Executing;
    executed_time++;
}

void Process::check_finished() {
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

int Process::get_pid() {
    return pid;
}

int Process::get_duration() {
    return duration;
}

int Process::get_priority() {
    return priority;
}

void Process::set_priority(int p) {
    priority = p;
}







