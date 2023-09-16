#include "utils.h"
#include <vector>

using namespace std;
using namespace utils;

Scheduler::Scheduler() = default;

Scheduler::~Scheduler() = default;

void Scheduler::fcfs(vector<Process *> &q) {
    // recupera o ponteiro para o primeiro processo do vetor
    Process * p = q.front();

    // verifica se o processo foi terminado
    if (p -> get_state() == Finished) {
        // retira o processo do vator "fila"
        q.erase(q.begin());
    }
}

void Scheduler::sjf (vector<Process *> &q) {
    // recupera o ponteiro para o primeiro processo do vetor
    Process * p = q.front();

    // verifica se o processo foi terminado
    if (p -> get_state() == Finished) {
        // retira o processo do vetor "fila"
        q.erase(q.begin());
    } else { // se o processo nao terminou
        // recupera o novo processo
        Process * new_p = q.back();
        // seta o estado do processo como "ready", "pronto"
        new_p -> set_state_ready();
        // seta a duracao como prioridade
        new_p -> set_priority(new_p -> get_duration());
        // percorre os processos do vetor processes
        for (int i = 0; i < q.size(); i++) {
            // verifica se a prioridade do prox processo e menor
            if (new_p -> get_priority() < q[i] -> get_priority()) {
                // retira o novo processo do vetor "fila"
                q.pop_back();
                // verefica se houve preempcao
                if (i == 0)
                    // atualiza o estado do processo preemptado
                    q.front() -> set_state_ready();
                // recoloca o processo na "fila" na posicao i
                q.insert(q.begin() + i, new_p);
                break;
            }
        }
        // declara variavel auxiliar "priority"
        int priority;
        // percorre os processos do vetor processes
        for (int i = 0; i < q.size(); i++) {
            // verifica se o processo nao e o escolhido no escalonamento
            if (q[i] -> get_pid() != q.front() -> get_pid()) {
                // aumenta a prioeidade do processo
                priority = q[i] -> get_priority() - 1;
                q[i] -> set_priority(priority);
            }
        }
    }
}


void Scheduler::preemptive_prio(vector<Process *> &q) {
    // recupera o ponteiro para o primeiro processo do vetor
    Process * p = q.front();

    // verifica se o processo foi terminado
    if (p -> get_state() == Finished) {
        // retira o processo do vetor "fila"
        q.erase(q.begin());
    } else { // se o processo nao terminou
        // recupera o novo processo
        Process * new_p = q.back();
        // seta o estado do processo como "ready", "pronto"
        new_p -> set_state_ready();
        // percorre os processos do vetor "fila" de processes
        for (int i = 0; i < q.size(); i++) {
            // verifica se a prioridade do novo processo e maior que a do processo de posicao i
            if (new_p -> get_priority() > q[i] -> get_priority()) {
                // retira o novo processo do vetor "fila"
                q.pop_back();

                // verefica se houve preempcao
                if (i == 0)
                    // atualiza o estado do processo preemptado
                    q.front() -> set_state_ready();

                // coloca o novo processo na posicao i
                q.insert(q.begin() + i, new_p);
                break;
            }
        }
        // declara variavel auxiliar "priority"
        int priority;
        // percorre os processos do vetor processes
        for (int i = 1; i < q.size(); i++) {
            // aumenta a prioeidade do processo
            priority = q[i] -> get_priority() - 1;
            q[i] -> set_priority(priority);
        }
    }
}

void Scheduler::non_preemptive_prio(vector<Process *> &q) {
    // recupera o ponteiro para o primeiro processo do vetor
    Process * p = q.front();

    // verifica se o processo foi terminado
    if (p -> get_state() == Finished) {
        // retira o processo do vetor "fila"
        q.erase(q.begin());
    } else { // se o processo nao terminou
        // recupera o novo processo
        Process * new_p = q.back();
        // seta o estado do processo como "ready", "pronto"
        new_p -> set_state_ready();
        // percorre os processos do vetor "fila" de processes
        for (int i = 1; i < q.size(); i++) {
            // verifica se a prioridade do novo processo e maior que a do processo de posicao i
            if (new_p -> get_priority() > q[i] -> get_priority()) {
                // retira o novo processo do vetor "fila"
                q.pop_back();
                // coloca o novo processo na posicao i
                q.insert(q.begin() + i, new_p);
                break;
            }
        }
        // declara variavel auxiliar "priority"
        int priority;
        // percorre os processos do vetor processes
        for (int i = 1; i < q.size(); i++) {
            // aumenta a prioeidade do processo
            priority = q[i] -> get_priority() - 1;
            q[i] -> set_priority(priority);
        }
    }
}

void Scheduler::round_robin(vector<Process *> &q) {
    // recupera o ponteiro para o primeiro processo do vetor
    Process * p = q.front();

    // verifica se o processo foi terminado
    if (p -> get_state() == Finished) {
        // retira o processo do vetor "fila"
        q.erase(q.begin());
    } else { // se o processo nao terminou
        // verifica se ha um novo processo
        if (q.back() -> get_state() == New) {
            // recupera o novo processo
            Process * new_p = q.back();
            // seta o estado do processo como "ready", "pronto"
            new_p -> set_state_ready();
        }
        // atualiza o estado do processo preemptado
        q.front() -> set_state_ready();
        // coloca o processo no fim da "fila"
        q.push_back(q.front());
        // retira o processo do inicio da "fila"
        q.erase(q.begin());
}
