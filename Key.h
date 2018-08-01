#ifndef KEY_H
#define KEY_H

template <typename T, typename U, int op>
class KEY {
public:
	T x; U y;
	KEY(){ return; }
	KEY(T _x):x(_x){}
	KEY(T _x, U _y):x(_x), y(_y){}
	~KEY() { return; }	
	
	KEY & operator = (const KEY &a) {
		x = a.x, y = a.y;
		return (*this);
	}
	
	friend int cmp(const KEY &a, const KEY &b) {
		if(op == 1) {
			if(a.x > b.x) return 1;
			else if(a.x == b.x) return 0;
			else return -1;		
		} else {
			if(a.x > b.x) return 1;
			if(a.x < b.x) return -1;
			if(a.y > b.y) return 1;
			if(a.y < b.y) return -1;
			return 0;
		}
	}
	
	friend bool operator > (const KEY &a, const KEY &b) {
		return cmp(a, b) > 0;
	}
	
	friend bool operator < (const KEY &a, const KEY &b) {
		return cmp(a, b) < 0;
	}
	
	friend bool operator >= (const KEY &a, const KEY &b) {
		return cmp(a, b) >= 0;
	}
	
	friend bool operator <= (const KEY &a, const KEY &b) {
		return cmp(a, b) <= 0;
	}
	
	friend bool operator == (const KEY &a, const KEY &b) {
		return cmp(a, b) == 0;
	}
};

#endif
