
#include <iostream>
#include <cstdio>
#include "user.h"
#include "Scanner.h"
#include "Enum.h"
#include "data_base.h"
#include "program.h"

using namespace std;

fstream in;

void Init() {
	bool fg;
	in.open("user_system.txt", fstream::in);
	if(!in) {
		Data_base <KEY < String <35>, String <35>, 1>, User> system_user;
		User root("root", "sjtu", "root", 7);		
		system_user.add(root, "user_system.txt", root.key, fg);
	} else in.close();
	
	in.open("act_system.txt", fstream::in);
	if(!in) {
		in.open("act_system.txt", fstream::out);
		int x = 0;
		in.write(reinterpret_cast<char *>(&x), sizeof(int));
		in.write(reinterpret_cast<char *>(&x), sizeof(int));
		in.write(reinterpret_cast<char *>(&x), sizeof(int));
		in.close();
	} else in.close();
	
	return;
}

int main() {
	Init();
	bool Exit = false;
	in.open("command.txt", fstream::in);
	Program program;
	char line[510];
	if(!in) {
		puts("shuomingwendang");
		program.Get_user(1);
		while(true) {
			program.ask(Exit);
			if(Exit) break;
		}		
	} else {
		program.Get_user(0);	
		while(in.getline(line, 510, '\n')) {
			if(line == "EOF") break;
			program.getmessage(line);
			if(!program.execute(Exit)) puts("Invalid");
			if(Exit) break;
		}
		in.close();
	}
	return 0;
}
