#include "utils.h"

using namespace utils;

explicit CreatorProcess::CreatorProcess(Kernel * k) {
    input_file.read_file();
    process_params = input_file.get_process_params();
    kernel = k;
}

CreatorProcess::~CreatorProcess() {}

void CreatorProcess::syscall() {
    time++;

    for (int i = 0; i < process_params.size(); i++) {
        if (process_params[i] -> get_creation_time() == time)
            kernel -> create_process(time, process_params[i] -> get_priority(), process_params[i] -> get_duration());
    }
}