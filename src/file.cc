#include "utils.h"
#include <iostream>
#include <fstream>

using namespace utils;

File::File() {
	const char* inputFilePath = INPUT_FILE;
	myfile.open(inputFilePath);
	if (!myfile.is_open()) {
		cout << "Erro ao abrir o arquivo!\n";
	}
}


File::~File() {
	for(long unsigned int i = 0; i < processes.size() ; i++) {
		ProcessParams *p = processes[i];
		delete p;
	}
}


void File::print_processes_params()  {
	vector<ProcessParams *>::iterator iter = processes.begin();

	for(iter; iter < processes.end(); iter++) {
		ProcessParams *p = *iter;
		cout << *p;
	}
}

vector<ProcessParams *> File::get_process_params() {
	return processes;
}

void File::read_file() {
	
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
