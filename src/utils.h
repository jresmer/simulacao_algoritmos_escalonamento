#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono> 
#include <thread>
#include <unistd.h>
#include <fstream>

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

enum Algorithm
{
    FCFS = 1,
    SJF = 2,
    NONPREEMPTIVEPRIO = 3,
    PREEMPTIVEPRIO = 4,
    ROUNDROBIN = 5
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
    int get_pid();
    int get_duration();
    int get_priority();
    State get_state();
    void set_state_ready();
    void check_finished();
    void set_turnaround(int tt);
    void set_wait_time(int wt);
    void set_priority(int p);
    void executed();
};


class OutputString {
private:
    int time_;
    int n_processes;

public:
    OutputString();
    explicit OutputString(int np);
    ~OutputString();
    void print_init();
    void print_line(vector<Process*> &processes);
    void print_final(vector<Process*> &procecess);
};

class CPU {
private:
    long int sp;            //stackPointer
    long int pc;            //programCounter
    long int st;            //status?
    long int* gp;          //registradores
    CreatorProcess* creator;
    Kernel kernel;

public: 
    CPU();
    ~CPU();
    void run();
    void set_so(Kernel &k);
};


class Scheduler {
private:

public:
    Scheduler();
    ~Scheduler();
    void fcfs(vector<Process *> &q, vector<Process *> &f);
    void sjf (vector<Process *> &q, vector<Process *> &f);
    void priority(vector<Process *> &q, vector<Process *> &f, bool non_preemptive);
    void round_robin(vector<Process *> &q, vector<Process *> &f);
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
    Scheduler scheduler;
    OutputString output_string;
    vector<ProcessParams *> processesParameters;
    vector<Process *> finished_processes;
    vector<Process *> process_queue;
    vector<context *> processes_context;
    int created_pid;
    int time;
    Algorithm algorithm;
    bool new_process = false;

public:
    Kernel();
    explicit Kernel(Algorithm a);
    ~Kernel();
    void create_process(int creation_time, int priority, int duration);
    void reset();
    context* scheduler_call();
    void init_io_call();
    void final_io_call();
    void io_call();
    void set_context(long int * gp, long int sp, long int pc, long int st, context* c);
};

class File
{

public:
	File();
	
	~File();

	void read_file();

	void print_processes_params();

    vector<ProcessParams *> get_process_params();

private:
	vector<ProcessParams *> processes;
	ifstream myfile; 
};

class CreatorProcess {
private:
    vector<ProcessParams *> process_params;
    Kernel * kernel;
    File input_file;
    int time = 0;
public:
    CreatorProcess();
    ~CreatorProcess();
    void syscall();
};


} // closing namespace utils
