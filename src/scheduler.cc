#include "utils.h"
#include <vector>

using namespace std;
using namespace utils;

Scheduler::Scheduler() {}

Scheduler::~Scheduler() {}

void Scheduler::fcfs(vector<Process *> &q, vector<Process *> &f) {
    // recupera o ponteiro para o primeiro processo do vetor
    Process * p = q.front();

    // verifica se o processo foi terminado
    if (p -> get_state() == Finished) {
        // retira o processo do vator "fila"
        q.erase(q.begin());
        // adiciona o processo ao vetor de processos finalizados
        f.push_back(p);
    }
}

void Scheduler::sjf (vector<Process *> &q, vector<Process *> &f) {
    // recupera o ponteiro para o primeiro processo do vetor
    Process * p = q.front();

    // verifica se o processo foi terminado
    if (p -> get_state() == Finished) {
        // retira o processo do vetor "fila"
        q.erase(q.begin());
        // adiciona o processo ao vetor de processos finalizados
        f.push_back(p);
    } else { // se o processo nao terminou
        // recupera o novo processo
        Process * new_p = q.back();
        // seta o estado do processo como "ready", "pronto"
        new_p -> set_state_ready();
        // retira o novo processo do vetor "fila"
        q.pop_back();
        // seta a duracao como prioridade
        new_p -> set_priority(new_p -> get_duration());
        // percorre os processos do vetor processes
        for (int i = 0; i < q.size(); i++) {
            // verifica se a prioridade do prox processo e menor
            if (new_p -> get_priority() < q[i] -> get_priority()) {
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


void Scheduler::priority(vector<Process *> &q, vector<Process *> &f, bool non_preemptive) {
    // recupera o ponteiro para o primeiro processo do vetor
    Process * p = q.front();

    // verifica se o processo foi terminado
    if (p -> get_state() == Finished) {
        // retira o processo do vetor "fila"
        q.erase(q.begin());
        // adiciona o processo ao vetor de processos finalizados
        f.push_back(p);
    } else { // se o processo nao terminou
        // recupera o novo processo
        Process * new_p = q.back();
        // seta o estado do processo como "ready", "pronto"
        new_p -> set_state_ready();
        // define preemptividade:
        int i;
        if (non_preemptive)
            i = 1;
        else
            i = 0;
        // percorre os processos do vetor "fila" de processes
        for (i; i < q.size(); i++) {
            // verifica se a prioridade do novo processo e maior que a do processo de posicao i
            if (new_p -> get_priority() > q[i] -> get_priority()) {
                // coloca o novo processo na posicao i
                q.insert(q.begin() + i, new_p);
                break;
            }
        }
    }
}

void Scheduler::round_robin(vector<Process *> &q, vector<Process *> &f) {
    // recupera o ponteiro para o primeiro processo do vetor
    Process * p = q.front();

    // verifica se o processo foi terminado
    if (p -> get_state() == Finished) {
        // retira o processo do vetor "fila"
        q.erase(q.begin());
        // adiciona o processo ao vetor de processos finalizados
        f.push_back(p);
    } else { // se o processo nao terminou
        // verifica se ha um novo processo
        if (q.back() -> get_state() == New) {
            // recupera o novo processo
            Process * new_p = q.back();
            // seta o estado do processo como "ready", "pronto"
            new_p -> set_state_ready();
            // seta a prioridade do novo processo para 2
            new_p -> set_priority(2);
        }
        // declara e inicializa variavel auxiliar priority
        int priority = q.front() -> get_priority();
        // verifica se o processo ja foi executado por 2 segs
        if (priority == 0) {
            // coloca o processo no fim da "fila"
            q.push_back(q.front());
            // retira o processo do inicio da "fila"
            q.erase(q.begin());
            // reseta a prioridade do processo
            q.front() -> set_priority(2);
        } else {
            // atualiza a prioridade do processo de acordo com seu tempo de cpu restante ate preempcao
            q.front() -> set_priority(q.front() -> get_priority() - 1);
        }
    }
}
