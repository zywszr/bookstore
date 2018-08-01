#ifndef SCANNER_H
#define SCANNER_H

#include <string>

using namespace std;

class Scanner {
private:
	std::string str;
	int pos, len;
public:
	Scanner() { 
		pos = len = 0; 
		return;
	}
	Scanner(const char *s) {
		pos = 0, len = 0;
		while(*s != '\0') str += *s, ++ s, ++ len;
		return;
	}
	~Scanner() { return; }
	Scanner & operator = (const Scanner &x) {
		str = x.str, pos = x.pos, len = x.len;
		return (*this);
	}
	void Input(const string &s) {
		pos = 0, len = s.length(), str = s;
		return;
	}
	void Input(const char *s) {
		len = 0, pos = 0, str = "";
		while(*s != '\0') str += *s, ++ s, ++ len;
		return;
	}
	bool HasMoreToken() { 
		for(int i = pos ; i < len ; ++ i) if(str[i] != ' ') return true;
		return false;
	}
	std::string NextToken() {
		std::string ret;
		while(pos < len && str[pos] == ' ') ++ pos;
		while(pos < len && str[pos] != ' ') ret += str[pos], ++ pos;
		return ret;
	}
	std::string NextToken_1() {
		while(pos < len && str[pos] == ' ') ++ pos;
		if(pos == len) return "";
		std::string ret;
		while(pos < len && str[pos] != '=') ret += str[pos], ++ pos;
		if(pos == len)	return "";
		ret += '=';
		++ pos;
		return ret;
	}
	std::string NextToken_2() {
		while(pos < len && str[pos] == ' ') ++ pos;
		if(pos == len || str[pos] != '"') return "";	
		std::string ret;
		ret += '"', ++ pos;
		while(pos < len && str[pos] != '"') ret += str[pos], ++ pos;
		if(pos == len) return "";
		ret += '"', ++ pos;
		return ret;
	}
	std::string NextToken_3() {
		while(pos < len && str[pos] == ' ') ++ pos;
		if(pos == len) return "";
		std::string ret;
		while(pos < len && str[pos] != ' ' && str[pos] != '|') ret += str[pos], ++ pos;
		//cout << "pos = " << pos << endl;
		while(pos < len && str[pos] != '|') ++ pos;
		++ pos;
		return ret;
	}
	std::string Get_str() {
		return str;
	}
};

#endif
