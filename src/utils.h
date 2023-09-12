#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono> 
#include <thread>
#include <unistd.h>

using namespace std;

namespace utils {

enum State
{
        New = 1,
        Ready = 2,
        Executing = 3,
        Finished = 4,
        NotCreated = 5
};

struct context
{
    long int sp;
    long int pc;
    long int status;
    long int * gp;
};


class Process {

private:
    int pid;
    int duration;
    int priority;
    int executed_time;
    int creation_time;
    int turnaround_time;
    int wait_time;
    State state;

public:
    Process();
    explicit Process(int ct, int d, int p, int id);
    ~Process();
    int func();
    int get_pid();
    int get_duration();
    int get_prioity();
    State get_state();
    void set_state_ready();
    void check_finished();
    void set_turnaround(int tt);
    void set_wait_time(int wt);
    void set_priority(int p);
};


class OutputString {
private:
    int time;
    int n_processes;

public:
    OutputString();
    explicit OutputString(int np);
    ~OutputString();
    void printInit();
    void printLine(vector<Process*> p);
    void printFinal(int tt, float tme, int nttc);
};

class CPU {
private:
    long int sp;            //stackPointer
    long int pc;            //programCounter
    long int st;            //status?
    long int* gp;          //registradores

public:
    CPU();
    ~CPU();
    void run(Process* p);
    void set_context(context *c);
    context* get_context();
};


class Scheduler {
private:
    vector<Process *> processes;
    int fcfs();
    int sjf ();
    int priority(bool non_preemptive);
    int round_robin();

public:
    Scheduler();
    explicit Scheduler(vector<Process *> &p);
    ~Scheduler();
    bool done();
    int run(int te);
    void add_process(Process * p);
};


class ProcessParams {
public:
    ProcessParams(int c, int d, int p);
    int get_creation_time();
    int get_duration();
    int get_priority();
    friend ostream &operator<<(ostream& os, const ProcessParams& p) {
        os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
        return os;
    }

private:
    int creation_time;
    int duration; //seconds
    int priority;
};


class Kernel {
private:
    CPU *cpu;
    Scheduler scheduler;
    OutputString outputString;
    vector<ProcessParams *> processesParameters;
    vector<Process *> processes;
    vector<context *> processesContext;
    int time;
    int created_pid;

public:
    Kernel();
    explicit Kernel(CPU *c, vector<ProcessParams *> pp);
    ~Kernel();
    void run(int te);
    void check_new_process();
    void create_process(ProcessParams *pp);
    void reset();

};


} // closing namespace utils
