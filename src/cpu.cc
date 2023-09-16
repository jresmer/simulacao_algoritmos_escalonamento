#include "utils.h"

using namespace utils;

CPU::CPU() {
    sp = 0;
    pc = 0;
    st = 0;
    gp = new long int[6];
    creator = new CreatorProcess();
}

CPU::~CPU() {
    delete[] gp;
}

void CPU::set_so(Kernel &k) {
    kernel = k;
    kernel.set_cpu(this);
    creator->set_kernel(&kernel);
}

void CPU::set_context(context* c) {
    sp = c -> sp;
    pc = c -> pc;
    st = c -> status;
    for (int i = 0; i < 6; i++)
        gp[i] = c -> gp[i];
}

context CPU::get_context() {
    context c;
    c.sp = sp;
    c.pc = pc;
    c.status = st;
    for (int i = 0; i < 6; i++)
        c.gp[i] = gp[i];

    return c;
}

//IMPLEMENTAR
void CPU::run() {
    // declara variavel auxiliar "process"
    Process* p;

    //Inicializa o input
    kernel.init_io_call();

    while (1) {
        // da tempo de cpu para que a processo criador crie processos filhos se for necessario
        creator -> syscall();
        // da tempo de cpu para que o kernel rode o escalanador caso necessario
        p = kernel.scheduler_call();
        // se nao houver processo escalonado encerra a simulacao (contexto da simulacao)
        if (p == nullptr) {
            kernel.final_io_call();
            break;
        }
        // roda o processo
        p -> run(gp, &sp, &pc, &st);
        // gera saida da iteracao (contexto da simulacao)
        kernel.io_call();
    }
}
