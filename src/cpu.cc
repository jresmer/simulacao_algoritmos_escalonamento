#include "utils.h"

using namespace utils;

CPU::CPU() {
    sp = 0;
    pc = 0;
    st = 0;
    gp = new long int[6];
    kernel = Kernel();
    creator = new CreatorProcess();
}

CPU::~CPU() {
    delete[] gp;
}

void CPU::set_so(Kernel &k) {
    kernel = k;
}

//IMPLEMENTAR
void CPU::run() {
    // declara variavel auxiliar "context"
    context * c;
    while (1) {
        // da tempo de cpu para que a processo criador crie processos filhos se for necessario
        creator -> syscall();
        // da tempo de cpu para que o kernel rode o escalanador caso necessario
        c = kernel.scheduler_call();
        // se nao houver processo escalonado encerra a simulacao (contexto da simulacao)
        if (c == NULL) {
            kernel.final_io_call();
            break;
        } else {
            // recupera o contexto do processo escalonado
            sp = c -> sp;
            pc = c -> pc;
            st = c -> status;
            for (int i = 0; i < 6; i++)
                gp[i] = c -> gp[i];
            
            // altera valor do sp
            sp += rand() % 1000;
            sp -= rand() % 700;
            // altera valor do pc
            pc += rand() % 1000;
            pc -= rand() % 700;
            // altera valor do registrador de status
            st += rand() % 1000;
            st -= rand() % 700;
            // altera os valores dos registradores de proposito geral
            for (int i = 0; i < 6; i++) {
                gp[i] += rand() % 1000;
                gp[i] -= rand() % 700;
            }

            

            kernel.set_context(gp, sp, pc, st, c);
        }

    }
}
