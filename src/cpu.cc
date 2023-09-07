#include "utils.h"

using namespace utils;

CPU::CPU() {
    sp = 0;
    pc = 0;
    st = 0;
    gp = new long int[6];
}

CPU::~CPU() {
    delete[] gp;
}

void CPU::run() {
    
}

context CPU::get_context() {
    context contexto;
    contexto.sp = sp;
    contexto.pc = pc;
    contexto.status = st;
    contexto.gp = gp;
    return contexto;
}

void CPU::set_context(context *c) {
    sp = c->sp;
    pc = c->pc;
    st = c->status;
    gp = c->gp; 
}
