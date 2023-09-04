#include "utils.h"

using namespace utils;

CPU::CPU(Process * processes) {
    sp = 0;
    pc = 0;
    st = 0;
    gp = new long int[6];
    process = processes;
}

CPU::~CPU() {
    delete[] gp;
    delete process;
}

void CPU::run() {
    
}

Process * CPU::get_process() {
    return process;
}

void CPU::set_process(Process * process_) {
    process = process_;
}


context CPU::get_context() {
    context contexto;
    contexto.sp = sp;
    contexto.pc = pc;
    contexto.status = st;
    contexto.gp = gp;
    return contexto;
}