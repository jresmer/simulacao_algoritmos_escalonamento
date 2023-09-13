#include "utils.h"
#include <vector>

using namespace std;
using namespace utils;

Scheduler::Scheduler() {
    processes = vector<Process*>();
}

Scheduler::~Scheduler() {
    for (Process* process : processes)
        delete process;
}

void Scheduler::add_process(Process* p) {
    processes.push_back(p);
}

int Scheduler::run(int escalonation_type) {
    int pid;
    switch(escalonation_type) {
        case 1:
            // first come first serve
            pid = fcfs();
            break;
        case 2:
            // shortest job first
            pid = sjf();
            break;
        case 3:
            // preemptive priority
            pid = priority(false);
            break;
        case 4:
            // non-preemptive priority
            pid = priority(true);
            break;
        case 5:
            // round-robin
            pid = round_robin();
            break;
        default:
            pid = -1;
            break;
    }

    return pid;
}

bool Scheduler::done() {
    // percorre os processos do vetor processes
    for (int i = 0; i < processes.size(); i++) {
        // verifica se o processo indexado na posicao i foi finalisado
        if (processes[i] -> get_state() == Finished)
            // o processo termminado do vetor
            processes.erase(processes.begin() + i); 
    }
    // verifica se o vetor processes se encontra vazio
    if (processes.empty())
        // retorna o valor booleano verdadiro
        return true;
    // caso o vetor nao estaja vazio retorna o valor booleano falso
    return false;
}

int Scheduler::fcfs() {
    // verefica se ha um processo a ser escalonado
    if (done())
        // retorna o valor "-1" que determina que nao houve processo escalonado
        return -1;
    // escolhe o primeiro processo
    return processes[0] -> get_pid();
}

int Scheduler::sjf () {
    // verefica se ha um processo a ser escalonado
    if (done())
        // retorna o valor "-1" que determina que nao houve processo escalonado
        return -1; 
    /*
    declaracao de variaveis auxiliares:
    - pid do processo escolhido
    - duracao do processo
    - prioridade do proceso
    - menor duracao encontrada
    */
    int pid;
    int duration;
    int priority;
    int shortest_duration = 10E20;    
    // percorre os processos do vetor processes
    for (int i = 0; i < processes.size(); i++) {
        // verifica se o processo e novo
        if (processes[i] -> get_state() == New) {
            /*  
            - seta o estado do processo para ready
            - atualiza o valor da prioridade do processo
            */
            processes[i] -> set_state_ready();
            priority = processes[i] -> get_duration();
            processes[i] -> set_priority(priority);
        }
        // verifica se o processo esta rodando
        if (processes[i] -> get_state() == Executing)
            // retorna o id do processo
            return processes[i] -> get_pid();
        // atualiza o valor da variavel auxiliar
        duration = processes[i] -> get_duration();
        // verifica se a duracao do processo e a menor ate agora
        if (duration < shortest_duration) {
            // atualiza os valores das variaveis auxiliares
            pid = processes[i] -> get_pid();
            shortest_duration = duration;
        }
    }
    // percorre os processos do vetor processes
    for (int i = 0; i < processes.size(); i++) {
        // verifica se o processo nao e o escolhido no escalonamento
        if (processes[i] -> get_pid() != pid) {
            // aumenta a prioeidade do processo
            priority = processes[i] -> get_prioity() - 1;
            processes[i] -> set_priority(priority);
        }
    }
    // retorna o id do processo escalonado
    return pid;
}


int Scheduler::priority(bool non_preemptive) {
    // verefica se ha um processo a ser escalonado
    if (done())
        // retorna o valor "-1" que determina que nao houve processo escalonado
        return -1;
    /*
    declaracao de variaveis auxiliares:
    - pid do processo escolhido
    - maior prioridade
    - prioridade do processo
    */
    int pid;
    int highest_priority;
    int priority;
    // percorre os processos do vetor processes
    for (int i = 0; i < processes.size(); i++) {
        // verifica se o processo e novo
        if (processes[i] -> get_state() == New)
            // seta o estado do processo para ready
            processes[i] -> set_state_ready();
        // verifica se o processo esta rodando
        if (processes[i] -> get_state() == Executing && non_preemptive) //conferir
            // retorna o id do processo
            return processes[i] -> get_pid();
        // atualiza o valor da variavel auxiliar
        priority = processes[i] -> get_prioity();
        // verifica se a prioridade do processo e a maior ate o momento
        if (priority > highest_priority) {
            // atualiza o processo escolhido
            highest_priority = priority;
            pid = processes[i] -> get_pid();
        }
    }
    // retorna o id do processo escalonado
    return pid;
}

int Scheduler::round_robin() {
    // verefica se ha um processo a ser escalonado
    if (done())
        // retorna o valor "-1" que determina que nao houve processo escalonado
        return -1;
    // setar todas as prioridades em 2
    // ao escalornar um processo reduzir sua prioridade em 1

    // percorre os processos do vetor processes
    for (int i = 0; i < processes.size(); i++) {
        if (processes[i] -> get_state() == New) {
            // seta o estado do processo para ready e a prioridade para 2
            processes[i] -> set_state_ready();
            processes[i] -> set_priority(2);
        }
        // verifica se o processo rodou por 1 seg
        if (processes[i] -> get_prioity() == 1) {
            // atualiza sua prioridade
            processes[i] -> set_priority(0);
            // escolhe o processo
            return processes[i] -> get_pid();
        }
        // verifica se o processo ainda nao executou sua vez
        if (processes[i] -> get_prioity() == 2) {
            // atualiza sua prioridade
            processes[i] -> set_priority(1);
            // escolhe o processo
            return processes[i] -> get_pid();
        }
    }
    // percorre os processos do vetor processes
    for (int i = 0; i < processes.size(); i++)
        // seta todas as prioridades para 2
        processes[i] -> set_priority(2);
    // seta a prioridade do primeiro processo do vetor para 1
    processes[0] -> set_priority(1);
    // escalona o primeiro processo do vetor
    return processes[0] -> get_pid();
}
