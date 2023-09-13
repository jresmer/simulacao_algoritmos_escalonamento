#include "utils.h"

using namespace utils;

ProcessParams::ProcessParams(int c, int d, int p) { 
		creation_time = c;
		duration = d;
		priority = p;
}

int ProcessParams::get_creation_time() {
	return creation_time;
}

int ProcessParams::get_duration() {
	return duration;
}

int ProcessParams::get_priority() {
    return priority;
}