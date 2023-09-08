#include "src/utils.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace utils;

class File
{

public:
	File() {
		myfile.open("entrada.txt");
		if (!myfile.is_open()) {
			cout << "Erro ao abrir o arquivo!\n";
		}
	}
	
	~File() {
		for(int i = 0; i < processes.size() ; i++) {
			ProcessParams *p = processes[i];
			delete p;
		}
	}

	void read_file() {
	
		int a, b, c;
		
		if (!myfile.is_open()) {
			cout << "Arquivo não está aberto!" << endl;
		}
		
		while (myfile >> a >> b >> c) {
			ProcessParams *p = new ProcessParams(a, b, c);
			processes.push_back(p);
		}

		cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
	}

	void print_processes_params() {
		vector<ProcessParams *>::iterator iter = processes.begin();

		for(iter; iter < processes.end(); iter++) {
			ProcessParams *p = *iter;
			cout << *p;
		}
	}

	vector<ProcessParams *> get_process_params() {
		return processes;
	}

private:
	vector<ProcessParams *> processes;
	ifstream myfile; 
};

int main()
{
	File f;
	f.read_file();
	f.print_processes_params();

    CPU ine5412 = CPU();
    Kernel k = Kernel(&ine5412, f.get_process_params());
	k.run(1);
	k.reset();

	k.run(2);
	k.reset();

	k.run(3);
	k.reset();

	k.run(4);
	k.reset();

	k.run(5);
	k.reset();

    k.~Kernel();
    ine5412.~CPU();
    f.~File();
}
