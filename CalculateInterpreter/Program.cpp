#include "Analysis.h"

#include <Windows.h>
#include <iostream>
#include <fstream>

typedef void (*Command)();

map<string, Command> commands;

void registCmd(string str, Command func) {
	commands[str] = func;
}

bool setcolor(int code) {
	return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code);
}

void calculate() {
	cout << "EXPRESSION>"; setcolor(0xB);
	string str;
	cin >> str;	setcolor(7);
	auto execution = commands.find(str);
	if (execution != commands.end())
		execution->second();
	else {
		Expression exp(str);
		cout << "RESULT>"; setcolor(0xA); cout << exp.formatValue() << endl; setcolor(7);
	}
}

void exit() {
	exit(0);
}
void help() {
	setcolor(3);
	cout << "=======[Lialy's expression interpreter]========" << endl;
	cout << "exit - ÍË³ö³ÌÐò." << endl;
	setcolor(7);
}

void fromFile(char*& path) {
	ifstream in;
	in.open(path, ios::in);
	char buffer[256];
	while (!in.eof()) {
		in.getline(buffer, 256, '\n');
		Expression exp(buffer);
		cout << buffer << ">"; setcolor(0xA); cout << exp.formatValue() << endl; setcolor(7);
	}
}
int main(int argc, char* argv[])
{
	if (argc > 1) {
		fromFile(argv[1]);
	}
	else {
		registCmd("exit", exit);
		registCmd("?", help);
		registCmd("£¿", help);
		registCmd("help", help);
		while (true)
			calculate();
	}
}

