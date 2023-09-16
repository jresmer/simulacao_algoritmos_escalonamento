#include "utils.h"

using namespace utils;

CreatorProcess::CreatorProcess(Kernel * k) {
    File f;
    f.read_file();
    f.print_processes_params();
    process_params = f.get_process_params();
    kernel = k;
    creator_time = 0;
}

CreatorProcess::~CreatorProcess() = default;

void CreatorProcess::syscall() {
    for (int i = 0; i < process_params.size(); i++) {
        if (process_params[i] -> get_creation_time() == creator_time)
            kernel -> create_process(creator_time, process_params[i] -> get_priority(), process_params[i] -> get_duration());
    }

    creator_time++;
}