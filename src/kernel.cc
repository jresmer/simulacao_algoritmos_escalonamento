#include "utils.h"

using namespace utils;

Kernel::Kernel() {
    cpu = new CPU();
    processes = vector<Process *>();
    processesContext = vector<context *>();
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
}

Kernel::~Kernel() {
    delete cpu; // <- necessario?

    for(int i = 0; i < processes.size() ; i++) {
        Process *p = processes[i];
        context *ctx = processesContext[i];
        delete p;
        delete ctx;
    }
}

void Kernel::run(int tipoDeEscalonamento) {
    bool executando = true;
    while (executando)
    {
        //Verifica se tem processos a serem criados
        if (processesParameters.size() > processes.size()) {
            check_new_process(created_pid);

        //Verifica se todos os processo criados ja foram finalizados
        } else {
            executando = scheduler.done();
        }

        //Roda o escalonador e busca qual processo deverá executar
        int pid;
        pid = scheduler.run(tipoDeEscalonamento);

        //Seta o contexto do processo na CPU, faz as alterações e pega o contexto modificado -> VERIFICAR
        /*
        cpu->set_context(processesContext[pid]);
        cpu->run();
        processesContext[pid] = cpu->get_context();
        */

        //Incrementa o tempo que se passou
        time++;
    }
    
}

//Verifica se precisa criar novos processos ao comparar o tempo atual com o tempo que o processo deve ser criado
void Kernel::check_new_process(int c_pid) {
    for(int i = 0; i < processesParameters.size(); i++) {
        ProcessParams *pp = processesParameters[i];
        if (pp->get_creation_time() == time) {
            create_process(pp, c_pid);
            created_pid++;
        }
    }
}

//Cria e armazena um processo e seu respectivo contexto
void Kernel::create_process(ProcessParams *pp, int c_pid) {
    Process *p = new Process(pp->get_creation_time(), pp->get_duration(), pp->get_priority(), c_pid);
    processes.push_back(p);
    scheduler.add_process(p);

    context *ctx = new context;
    ctx->pc = 0;
    ctx->sp = 0;
    ctx->status = New;
    ctx->gp = new long int [6];
    processesContext.push_back(ctx);
}

void Kernel::reset() {
    for (int i = 0; i < processes.size(); ++i) {
        Process *p = processes[i];
        context *ctx = processesContext[i];
        delete ctx;
        delete p;
    }

    processes = vector<Process *>();
    processesContext = vector<context *>();
    time = 0;
    created_pid = 0;

}