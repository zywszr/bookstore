#ifndef STRING_H
#define STRING_H

#include <string>
#include <cstring>

using namespace std;

template <int len>
class String {
	
private:
	char c[len];
public:
	String() { 
		c[0] = '\0';
		return; 
	}
	~String() { return; }
	void Set(const char *s) {
		memset(c, 0, len);
		memcpy(c, s, len);
		c[strlen(s)] = '\0';
		return;
	}
	void Set(const std::string &s) {
		memset(c, 0, len);
		memcpy(c, s.c_str(), len);
		c[s.length()] = '\0';
		return;
	}
	String(const string &s) {
		memset(c, 0, len);
		memcpy(c, s.c_str(), len);
		c[s.length()] = '\0';
		return;
	}
	String(const char *s) {
		memset(c, 0, len);
		memcpy(c, s, len);
		c[strlen(s)] = '\0';
		return;
	}
	String & operator = (const char *s) {
		Set(s);
		return (*this);
	}
	String & operator = (const string &s) {
		Set(s);
		return (*this);
	}
	String & operator = (const String &s) {
		Set(s.c);
		return (*this);
	}
	
	friend ostream & operator << (ostream & os, const String &st) {
		os << st.c;
		return os;
	}
	operator string() const { return c; }
	
	friend int cmp(const String &x, const String &y) {
		return strcmp(x.c, y.c);
	}
	
	friend bool operator > (const String &a, const String &b) {
		return cmp(a, b) > 0;
	}
	
	friend bool operator < (const String &a, const String &b) {
		return cmp(a, b) < 0;
	}
	
	friend bool operator >= (const String &a, const String &b) {
		return cmp(a, b) >= 0;
	}
	
	friend bool operator <= (const String &a, const String &b) {
		return cmp(a, b) <= 0;
	}
	
	friend bool operator == (const String &a, const String &b) {
		return cmp(a, b) == 0;
	}
	
	friend bool operator != (const String &a, const String &b) {
		return !(cmp(a, b) == 0);
	}
};


#endif
