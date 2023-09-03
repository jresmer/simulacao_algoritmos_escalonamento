#pragma once
#include <string>
#include <chrono> 
#include <thread>
#include <unistd.h>

namespace utils {

enum State
{
        New = 1,
        Ready = 2,
        Executing = 3,
        Finished = 4
};

struct context
{
    long int sp;
    long int pc;
    long int status;
    long int * gp;
};

class OutputString {
    private:
    public:
        OutputString();
        ~OutputString();
        void printInit(int np);
        void printDiagram(int np, int ti, Process*processos);
        void printFinal(int tt, float tme, int nttc);
};

class Scheduler {

    private:
        CPU cpu;
        Process ** processes;
        bool done();

    public:
        Scheduler();
        explicit Scheduler(); // rever
        ~Scheduler();
        void fcfs();
        void sjf ();
        void preemptive_priority();
        void non_preemptive_priority();
        void round_robin();
};

class CPU {

    private:
        long int sp;            //stackPointer
        long int pc;            //programCounter
        long int st;            //status?
        long int * gp;          //registradores
        Process * process;      //processos

    public:
        CPU();
        explicit CPU(Process * processes);
        ~CPU();
        void run();
        Process * get_process();
        void set_process(Process * process_);
        context get_context();
};



class Process {

    private:
        int creation_time;
        int duration;
        int priority;
        int turnaround_time;
        int executed_time;
        int wait_time;
        State state;

    public:
        Process();
        explicit Process(int ct, int d, int p);
        ~Process();
        void func(int d);
        void set_turnaround(int tt);
        void set_wait_time(int wt);
        void set_state_ready();
        State get_state();
};

} // closing namespace utils
