#include "utils.h"

using namespace utils;

CreatorProcess::CreatorProcess() {}

CreatorProcess::~CreatorProcess() {}

void CreatorProcess::syscall() {
    time++;

    for (int i = 0; i < process_params.size(); i++) {
        if (process_params[i] -> get_creation_time() == time)
            kernel -> create_process(time, process_params[i] -> get_priority(), process_params[i] -> get_duration());
    }
}