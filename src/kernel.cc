#include "utils.h"
#include <iterator>

using namespace utils;
using namespace std;

Kernel::Kernel() {
    process_queue = vector<Process *>();
    processes = vector<Process *>();
    processes_context = vector<context *>();
    scheduler = Scheduler();
    output_string = OutputString();
    created_pid = 0;
    kernel_time = 0;
    algorithm = FCFS;
}

Kernel::Kernel(Algorithm a) {
    process_queue = vector<Process *>();
    processes = vector<Process *>();
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

    for (int i = 0; i < processes.size(); ++i) {
        Process *p = processes[i];
        delete p;
    }

    for (int i = 0; i < processes_context.size(); ++i) {
        context *c = processes_context[i];
        delete c;
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

    for (int i = 0; i < processes.size(); ++i) {
        Process *p = processes[i];
        delete p;
    }

    for (int i = 0; i < processes_context.size(); ++i) {
        context *c = processes_context[i];
        delete c;
    }

    process_queue = vector<Process *>();
    processes = vector<Process *>();
    processes_context = vector<context *>();
    created_pid = 0;
    kernel_time = 0;
}

void Kernel::init_io_call() {
    output_string.print_init();
}

void Kernel::final_io_call() {
    output_string.print_final(processes);
}

void Kernel::io_call() {
    output_string.print_line(processes, kernel_time);
}

void Kernel::set_algorithm(Algorithm a) {
    algorithm = a;
}

Process * Kernel::scheduler_call() {
    // confere se ha processsos na "fila"
    if (process_queue.empty())
        return nullptr;
    // recupera o estado do processo em execucao
    State s = process_queue[0] -> get_state();
    // atualiza o contador de tempo
    kernel_time++;

    // define se se configura caso de escalonamento
    // escolhe o algoritmo de escalonamento
    switch (algorithm)
    {
    case FCFS:
        if (s == Finished || new_process) {
            // recupera o contexto da cpu
            set_context(cpu_ -> get_context(), process_queue[0] -> get_pid());
            // chama o escalonador
            scheduler.fcfs(process_queue);
            // garante o valor "false" para a variavel booleana "new_process"
            new_process = false;
        }
        break;
    
    case SJF:
        if (s == Finished || new_process) {
            // recupera o contexto da cpu
            set_context(cpu_ -> get_context(), process_queue[0] -> get_pid());
            // chama o escalonador
            scheduler.sjf(process_queue);
            // garante o valor "false" para a variavel booleana "new_process"
            new_process = false;
        }
        break;

    case NONPREEMPTIVEPRIO:
        if (s == Finished || new_process) {
            // recupera o contexto da cpu
            set_context(cpu_ -> get_context(), process_queue[0] -> get_pid());
            // chama o escalonador
            scheduler.priority(process_queue, true);
            // garante o valor "false" para a variavel booleana "new_process"
            new_process = false;
        }
        break;

    case PREEMPTIVEPRIO:
        if (s == Finished || new_process) {
            // recupera o contexto da cpu
            set_context(cpu_ -> get_context(), process_queue[0] -> get_pid());
            // chama o escalonador
            scheduler.priority(process_queue, false);
            // garante o valor "false" para a variavel booleana "new_process"
            new_process = false;
        }
        break;
    
    case ROUNDROBIN:
        if (s == Finished || kernel_time % 2 == 0 || new_process) {
            // recupera o contexto da cpu
            set_context(cpu_ -> get_context(), process_queue[0] -> get_pid());
            // chama o escalonador
            scheduler.round_robin(process_queue);
            // garante o valor "false" para a variavel booleana "new_process"
            new_process = false;
        }
        break;
    }

    // seta o contexto do processo na cpu
    cpu_ -> set_context(processes_context[process_queue[0] -> get_pid()]);
    // retorna um ponteiro para o processo escalonado
    return process_queue[0];
}

context* Kernel::get_context(int pid) {
    return processes_context[pid];
}

void Kernel::set_context(context c, int pid) {
    // atualiza os valores dos registradores - sp, pc, st - do processo de cujo process id e "pid"
    processes_context[pid] -> sp = c.sp;
    processes_context[pid] -> pc = c.pc;
    processes_context[pid] -> status = c.status;
    // atualiza os valores dos registradores de proposito geral do processo de cujo process id e "pid"
    for (int i = 0; i < 6; i++)
        processes_context[pid] -> gp[i] = c.gp[i];
}

void Kernel::set_cpu(CPU* cpu) {
    cpu_ = cpu;
}
