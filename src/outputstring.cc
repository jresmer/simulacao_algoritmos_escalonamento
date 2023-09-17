#include "utils.h"
#include <iomanip>

using namespace utils;
using std::setw;

OutputString::OutputString() = default;


OutputString::~OutputString() = default;

// Header of print
void OutputString::print_init(Algorithm a) {
    string algorithm = get_algorithm_to_string(a);

    cout << "\n\nTime  ->   Processes - " << algorithm;

    cout << "\n";
    cout.flush();
}

void OutputString::print_line(vector<Process*> &procecess, int time_) { // atualizar
    cout << setfill('0') << setw(2) << time_ << "-" << setw(2) << time_ + 1 << "   ";

    for (long unsigned int i = 0; i < procecess.size(); ++i) {
        State p_state = NotCreated;

        if (i < procecess.size()) {
            for (long unsigned int j = 0; j < procecess.size(); ++j) {
                if (static_cast<unsigned long int>(procecess[j]->get_pid()) == i) {
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

void OutputString::print_final(vector<Process*> &processes) {
    int n_processes = processes.size();
    int turnaround_time = 0;
    int avg_wait_time = 0;

    cout << "\n";

    for (int i = 0; i < n_processes; i++) {
        turnaround_time += processes[i] -> get_turnaround_time();
        avg_wait_time += processes[i] -> get_wait_time();
        cout << "P" << processes[i] -> get_pid() << " Turnaround Time: " << processes[i] -> get_turnaround_time() << endl;
    }

    cout << "\n";

    avg_wait_time = float(avg_wait_time) / float(n_processes);
    cout << "Average Wait Time: " << avg_wait_time << endl;
    turnaround_time = float(turnaround_time) / float(n_processes);
    cout << "Average Turnaround Time: " << turnaround_time << endl;
}

string OutputString::get_algorithm_to_string (Algorithm a) {
    switch (a) {
        case Algorithm::FCFS:
            return "FCFS";
        case Algorithm::SJF:
            return "SJF";
        case Algorithm::NONPREEMPTIVEPRIO:
            return "Non-preemptive Priority";
        case Algorithm::PREEMPTIVEPRIO:
            return "Preemptive Priority";
        case Algorithm::ROUNDROBIN:
            return "Round Robin";
        default:
            return "Unknown"; // Handle unknown enum values gracefully
    }
}
