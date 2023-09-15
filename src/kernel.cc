#include "utils.h"
#include <iterator>

using namespace utils;
using namespace std;

Kernel::Kernel() {
    process_queue = vector<Process *>();
    finished_processes = vector<Process *>();
    processes_context = vector<context *>();
    scheduler = Scheduler();
    output_string = OutputString();
    created_pid = 0;
    kernel_time = 0;
    algorithm = FCFS;
}

Kernel::Kernel(Algorithm a) {
    process_queue = vector<Process *>();
    finished_processes = vector<Process *>();
    processes_context = vector<context *>();
    scheduler = Scheduler();
    output_string = OutputString();
    kernel_time = 0;
    created_pid = 0;
    algorithm = a;
}

Kernel::~Kernel() {

    for (int i = 0; i < process_queue.size(); ++i) {
        Process *p = process_queue[i];
        delete p;
    }

    for (int i = 0; i < finished_processes.size(); ++i) {
        Process *p = finished_processes[i];
        delete p;
    }

    for (int i = 0; i < processes_context.size(); ++i) {
        Process *p = finished_processes[i];
        delete p;
    }
}

//Cria e armazena um processo e seu respectivo contexto
void Kernel::create_process(int creation_time, int priority, int duration) {
    Process* p = new Process(creation_time, duration, priority, created_pid);
    process_queue.push_back(p);

    context* ctx = new context;
    ctx->pc = 0;
    ctx->sp = 0;
    ctx->status = New;
    ctx->gp = new long int [6];
    processes_context.push_back(ctx);
    created_pid++;

    new_process = true;
    scheduler_call();
}

void Kernel::reset() {
    for (int i = 0; i < process_queue.size(); ++i) {
        Process *p = process_queue[i];
        delete p;
    }

    for (int i = 0; i < finished_processes.size(); ++i) {
        Process *p = finished_processes[i];
        delete p;
    }

    for (int i = 0; i < processes_context.size(); ++i) {
        Process *p = finished_processes[i];
        delete p;
    }

    process_queue = vector<Process *>();
    finished_processes = vector<Process *>();
    processes_context = vector<context *>();
    created_pid = 0;
    kernel_time = 0;
}

void Kernel::init_io_call() {
    output_string.print_init();
}

void Kernel::final_io_call() {
    output_string.print_final(finished_processes);
}

void Kernel::io_call() {
    vector<Process *> aux = vector<Process *>();
    aux.insert(aux.end(), make_move_iterator(finished_processes.begin()), make_move_iterator(finished_processes.end()));
    aux.insert(aux.end(), make_move_iterator(process_queue.begin()), make_move_iterator(process_queue.end()));

    output_string.print_line(aux, kernel_time);
}

void Kernel::set_context(long int* gp, long int sp, long int pc, long int st, context* c) {
    c -> sp = sp;
    c -> pc = pc;
    c -> status = st;
    for (int i = 0; i < 6; i++)
        c -> gp[i] = gp[i];
}

void Kernel::set_algorithm(Algorithm a) {
    algorithm = a;
}

context * Kernel::scheduler_call() {
    if (process_queue.empty())
        return nullptr;

    State s = process_queue[0] -> get_state();
    kernel_time++;

    // define se se configura caso de escalonamento
    // escolhe o algoritmo de escalonamento
    switch (algorithm)
    {
    case FCFS:
        if (s == Finished || new_process) {
            scheduler.fcfs(process_queue, finished_processes);
            new_process = false;
        }
        break;
    
    case SJF:
        if (s == Finished || new_process) {
            scheduler.sjf(process_queue, finished_processes);
            new_process = false;
        }
        break;

    case NONPREEMPTIVEPRIO:
        if (s == Finished || new_process) {
            scheduler.priority(process_queue, finished_processes, true);
            new_process = false;
        }
        break;

    case PREEMPTIVEPRIO:
        if (s == Finished || new_process) {
            scheduler.priority(process_queue, finished_processes, false);
            new_process = false;
        }
        break;
    
    case ROUNDROBIN:
        if (s == Finished || kernel_time % 2 == 0 || new_process) {
            scheduler.round_robin(process_queue, finished_processes);
            new_process = false;
        }
        break;
    }

    // retorna o contexto do processo escalonado
    process_queue[0] -> executed();
    return processes_context[process_queue[0] -> get_pid()];
}