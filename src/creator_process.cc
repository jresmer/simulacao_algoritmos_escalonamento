#include "utils.h"

using namespace utils;

CreatorProcess::CreatorProcess() {
    input_file.read_file();
    input_file.print_processes_params();
    process_params = input_file.get_process_params();
    creator_time = 0;
}

CreatorProcess::~CreatorProcess() = default;

void CreatorProcess::syscall() {
    for (long unsigned int i = 0; i < process_params.size(); i++) {
        if (process_params[i] -> get_creation_time() == creator_time)
            kernel -> create_process(creator_time, process_params[i] -> get_priority(), process_params[i] -> get_duration());
    }

    creator_time++;
}

void CreatorProcess::set_kernel(Kernel *k) {
    kernel = k;
}