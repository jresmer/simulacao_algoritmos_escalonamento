#include "utils.h"
#include <iomanip>

using namespace utils;
using std::setw;

OutputString::OutputString() {}

OutputString::OutputString(int np) {
    n_processes = np;
    time = 0;
    printInit();
}

OutputString::~OutputString() {

}

// Header of print
void OutputString::printInit() {
    cout << "\nTime    ";
    for (int i = 0; i < n_processes; ++i) {
        cout << "P" << i+1 << "    ";
    }
    cout << "\n";
    cout.flush();
}

void OutputString::printLine(vector<Process*> procecess) {
    cout << time << "-" << time+1 << "     ";

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
    cout << "\n";
    cout.flush();
    time++;
}

void OutputString::printFinal(int tt, float tme, int nttc) {
    // Implementar
}