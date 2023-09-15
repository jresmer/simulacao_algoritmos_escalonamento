#include "utils.h"
#include <iomanip>

using namespace utils;
using std::setw;

OutputString::OutputString() = default;


OutputString::~OutputString() = default;

// Header of print
void OutputString::print_init() {
    cout << "\nTime    ";

    /*
    for (int i = 0; i < n_processes; ++i) {
        cout << "P" << i+1 << "    ";
    }
    */

    cout << "\n";
    cout.flush();
}

void OutputString::print_line(vector<Process*> &procecess, int time_) { // atualizar
    cout << setfill('0') << setw(2) << time_ << "-" << setw(2) << time_ + 1 << "   ";

    /*
    for (int i = 0; i < n_processes; ++i) {
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
            case Ready or New:
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
    */
    cout << "\n";
    cout.flush();
}

void OutputString::print_final(vector<Process*> &procecess) {
    // Implementar
}