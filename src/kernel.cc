#include "utils.h"

using namespace utils;

Kernel::Kernel() {
    cpu = new CPU();
    processes = vector<Process *>();
    processesParameters = vector<ProcessParams *>();
    scheduler = Scheduler();
    created_pid = 0;
}

Kernel::Kernel(CPU *c, vector<ProcessParams *> p) {
    cpu = c;
    processesParameters = p;
    processes = vector<Process *>();
    processesContext = vector<context *>();
    scheduler = Scheduler();
    created_pid = 0;


    for (int i = 0; i < processes.size(); ++i) {
       
    }
}

Kernel::~Kernel() {
    delete cpu;

    for(int i = 0; i < processes.size() ; i++) {
        Process *p = processes[i];
        context *c = processesContext[i];
        delete p;
        delete c;
    }
}

void Kernel::run(int tipoDeEscalonamento) {
    
    bool executando = true;
    while (executando)
    {
        if (processesParameters.size() > processes.size()) {
            //Verifica se tem processos a serem criados
            check_new_process(created_pid);    
        } else { 
            //Verifica se todos os processo criados ja foram finalizados
            executando = scheduler.done();
        }
        int pid;
        scheduler.run(tipoDeEscalonamento);
        
        cpu->set_context();
        cpu->run();
        cpu->get_context();

        time++;
    }
    
}

void Kernel::check_new_process(int created_pid) {
    for(int i = 0; i < processesParameters.size(); i++) {
        ProcessParams *pp = processesParameters[i];
        if (pp->get_creation_time() == time) {
            create_process(pp, created_pid);
        }
    }
}

void Kernel::create_process(ProcessParams *pp, int created_pid) {
    Process *p = new Process(pp->get_creation_time(), pp->get_duration(), pp->get_priority(), created_pid);
    processes.push_back(p);
    scheduler.add_process(p);

    context *ctx = new context;
    ctx->pc = 0;
    ctx->sp = 0;
    ctx->status = New;
    ctx->gp = new long int [6];
    processesContext.push_back(ctx);
}