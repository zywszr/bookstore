#ifndef ENUM_H
#define ENUM_H

#include <string>

using namespace std;

enum OPERATOR {  
	LOAD, EXIT, SU, LOGOUT, USERADD, REGISTER, DELETE, PASSWD, SELECT, MODIFY, IMPORT, SHOW, BUY, REPORT, LOG, OTHER
};

OPERATOR stringtoope(string s) {
	if(s == "load") return LOAD;
	if(s == "exit") return EXIT;
	if(s == "su") return SU;
	if(s == "logout") return LOGOUT;
	if(s == "useradd") return USERADD;
	if(s == "register") return REGISTER;
	if(s == "delete") return DELETE;
	if(s == "passwd") return PASSWD;
	if(s == "select") return SELECT;
	if(s == "modify") return MODIFY;
	if(s == "import") return IMPORT;
	if(s == "show") return SHOW;
	if(s == "buy") return BUY;
	if(s == "report") return REPORT;
	if(s == "log") return LOG;
	return OTHER;
}

#endif
