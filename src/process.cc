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

void Process::set_turnaround() {
    turnaround_time = duration + wait_time;
}

void Process::increase_wait_time() {
    wait_time++;
}

void Process::run(long int* gp, long int* sp, long int* pc, long int* st) {
    state = Executing;
    executed_time++;

    // altera valor do sp
    sp += rand() % 1000;
    sp -= rand() % 700;
    // altera valor do pc
    pc += rand() % 1000;
    pc -= rand() % 700;
    // altera valor do registrador de status
    st += rand() % 1000;
    st -= rand() % 700;
    // altera os valores dos registradores de proposito geral
    for (int i = 0; i < 6; i++) {
        gp[i] += rand() % 1000;
        gp[i] -= rand() % 700;
    }

    //sleep(1);

}

void Process::check_finished() {
    if (executed_time == duration) {
        state = Finished;
        set_turnaround();
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

void Process::get_wait_time() {
    return wait_time;
}

void Process::get_turnaround_time() {
    return turnaround_time;
}







