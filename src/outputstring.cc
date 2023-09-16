#include "utils.h"
#include <iomanip>

using namespace utils;
using std::setw;

OutputString::OutputString() = default;


OutputString::~OutputString() = default;

// Header of print
void OutputString::print_init() {
    cout << "\nTime  ->   Processes";

    cout << "\n";
    cout.flush();
}

void OutputString::print_line(vector<Process*> &procecess, int time_) { // atualizar
    cout << setfill('0') << setw(2) << time_ << "-" << setw(2) << time_ + 1 << "   ";

    for (int i = 0; i < procecess.size(); ++i) {
        State p_state = NotCreated;

        if (i < procecess.size()) {
            for (int j = 0; j < procecess.size(); ++j) {
                if (procecess[j]->get_pid() == i) {
                    p_state = procecess[i]->get_state();
                    break;
                }
            }
        }

        switch (p_state) {
            case New:
                cout << "--    ";
                break;
            case Ready:
                cout << "--    ";
                break;
            case Executing:
                cout << "##    ";
                break;
            default:
                cout << "      ";
                break;
        }
    }

    cout << "\n";
    cout.flush();
}

void OutputString::print_final(vector<Process*> &procecess) {
    int n_processes = processes.size()
    int turnaround_time = 0;
    int avg_wait_time = 0;
    // Implementar
    for (int i = 0; i < n_processes; i++) {
        turnaround_time += processes[i] -> get_turnaround_time();
        avg_wait_time += processes[i] -> get_wait_time();
        cout << "P" << processes[i] -> get_pid() << ": " << processes[i] -> get_turnaround_time() << endl;
    }
    avg_wait_time = avg_wait_time / n_processes;
    cout << "Average wait time : " << avg_wait_time << endl;
    turnaround_time = turnaround_time / n_processes;
    cout << "Average Turnaround Time" << turnaround_time << endl;
}
