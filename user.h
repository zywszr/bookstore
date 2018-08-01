#ifndef USER_H
#define USER_H
#include "String.h"
#include "Key.h"

class User {
public:
	String <35> id, passwd, name; int k;
	KEY < String <35>, String <35>, 1> key;
	User() {
		k = 0; 
		return;
	}
	User(const char *_id, const char *_passwd, const char *_name, int _k):k(_k) {
		id.Set(_id), passwd.Set(_passwd), name.Set(_name);
		key.x = id, key.y = "";		
		return;
	}
	User & operator = (const User &other) {
		id = other.id, passwd = other.passwd, name = other.name;
		k = other.k, key = other.key;
		return (*this);
	}
};

#endif  
