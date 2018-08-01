#ifndef TOOL_H
#define TOOL_H

#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

string integerToString(int n) {
   ostringstream stream;
   stream << n;
   return stream.str();
}

bool StringToInteger(string str, int &k) {
   	istringstream stream(str);
   	int value;
   	stream >> value >> ws;
   	if(stream.fail() || !stream.eof()) return false;
   	else {
		k = value;
		return true;
	}
}

string realToString(double d) {
   ostringstream stream;
   stream << uppercase << d;
   return stream.str();
}

bool StringToReal(string str, double &k) {
   	istringstream stream(str);
   	double value;
   	stream >> value >> ws;
   	if(stream.fail() || !stream.eof()) return false;
   	else {
		k = value;
		return true;
	}
}

#endif
