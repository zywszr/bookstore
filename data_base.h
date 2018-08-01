#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <cstring>
#include <cstdio>
#include "String.h"

const int BLOCK_MAX = 250;
const int BLOCK_MIN = 100;

class act {
public:
	String <35> id; String <210> action;
	friend bool operator == (const act &x, const act &y) {
		return x.id == y.id;
	}
	friend ostream & operator << (ostream & os, const act &st) {
		os << "用户 " << st.id << " " << st.action;
		return os;
	}
};

template <typename K, typename T>
class Data_base {

private:
	fstream in; 
public:
	Data_base() { return; }
	~Data_base() { return; }
	
	void Get_(int &pre, int &nxt, int &last, K &s) {
		in.read(reinterpret_cast<char *>(&pre), sizeof(int));
		in.read(reinterpret_cast<char *>(&nxt), sizeof(int));
		in.read(reinterpret_cast<char *>(&last), sizeof(int));
		in.read(reinterpret_cast<char *>(&s), sizeof(K));
		return;
	}
	
	void Inseekg(int last, int k = 1) {
		if(last == 0) {
			puts("shitttt");
			while(1);
			return;
		}
		in.clear(ios::goodbit);
		in.seekg((last - 1) * (3 * sizeof(int) + sizeof(K) + sizeof(T)) + (2 + k) * sizeof(int), ios::beg);
		return;
	}
	
	void Inseekp(int last, int k) {
		if(last == 0) {
			puts("shitttt");
			while(1);
		}
		in.clear(ios::goodbit);
		in.seekp((last - 1) * (3 * sizeof(int) + sizeof(K) + sizeof(T)) + (2 + k) * sizeof(int), ios::beg);
		return;
	}
	
	int Get(int num, int k) {
		int ret;
		if(num != 0) Inseekg(num, k);
		else {
		in.clear(ios::goodbit);
			in.seekg(sizeof(int) * (k - 1), ios::beg); 
		}
		in.read(reinterpret_cast<char *>(&ret), sizeof(int));
		return ret;	
	}
	void Write_num(int pos_1, int pos_2, int k) {
		if(pos_1 == 0) in.clear(ios::goodbit),in.seekp(sizeof(int) * (pos_2 - 1), ios::beg);
		else Inseekp(pos_1, pos_2);
		in.write(reinterpret_cast<char *>(&k), sizeof(int));
		return;
	}
	
	void Write_K(int pos, const K &s) {
		Inseekp(pos, 4);
		in.write(reinterpret_cast<const char *>(&s), sizeof(K));
		return;
	}
	
	void Write_type(int pos, const T &x) {
		Inseekp(pos, 4);
		in.seekp(sizeof(K), ios::cur);
		in.write(reinterpret_cast<const char *>(&x), sizeof(T));
		return;
	}
	
	
	int find_mn(const K &k, int op = 0) {
		int num = Get(0, 2), st = Get(0, 3), sum = Get(0, 1), ret = 0;
		int pre1, nxt1, last1;
		int pre2, nxt2, last2;
		K s1, s2;
		
		if(sum == 0) return 0;
		
		Inseekg(st);
		Get_(pre1, nxt1, last1, s1);
		Inseekg(last1);
		Get_(pre2, nxt2, last2, s2);
		
		while(true) {
			if((op == 0 && s2 > k) || (op == 1 && s2.x > k.x)) {
				int nxt = nxt1, nw = st;
				K s; Inseekg(st, 4);
				in.read(reinterpret_cast<char *>(&s), sizeof(K));
				while(true) {
					if((op == 0 && s > k) || (op == 1 && s.x > k.x)) break;
					ret = nw;
					if(nw == last1) break;
					nw = nxt;
					nxt = Get(nw, 2);		
					Inseekg(nw, 4);
					in.read(reinterpret_cast<char *>(&s), sizeof(K));
				}
				break;
			}
			ret = last1;
			if(nxt2 == 0) break;
			st = nxt2;
			Inseekg(st);
			Get_(pre1, nxt1, last1, s1);
			Inseekg(last1);
			Get_(pre2, nxt2, last2, s2);
		}
		return ret;
	}
	
	int find_mx(const K &k, int op = 0) {
		int num = Get(0, 2), st = Get(0, 3), sum = Get(0, 1), ret = 0;
		int pre1, nxt1, last1;
		int pre2, nxt2, last2;
		K s1, s2;
		if(sum == 0) return 0;
		Inseekg(st);
		Get_(pre1, nxt1, last1, s1);
		Inseekg(last1);
		Get_(pre2, nxt2, last2, s2);
		while(true) {
			//cout << "s2.num = " << s2.y << "k.num = " << k.y << endl;
			if((op == 0 && s2 >= k) || (op == 1 && s2.x >= k.x)) {
				int nxt = nxt1, nw = st; 
				K s; Inseekg(st, 4);
				in.read(reinterpret_cast<char *>(&s), sizeof(K));
				while(true) {
					if((op == 0 && s >= k) || (op == 1 && s.x >= k.x)) {
						ret = nw;
						break;
					}
					if(nw == last1) break;
					nw = nxt;
					nxt = Get(nw, 2);		
					Inseekg(nw, 4);
					in.read(reinterpret_cast<char *>(&s), sizeof(K));
				}
				break;
			}
			if(nxt2 == 0) break;
			st = nxt2;
			Inseekg(st);
			Get_(pre1, nxt1, last1, s1);
			Inseekg(last1);
			Get_(pre2, nxt2, last2, s2);
		}
		
		return ret;
	}
	
	
	int Get_size(int _last) {
		int ret = 0;
		int nw = _last;
		while(nw != 0 && Get(nw, 3) == _last) ++ ret, nw = Get(nw, 1);
		return ret;
	}
	
	int Find_pre(int nw, int k) {
		for(int i = 1 ; i <= k ; ++ i) nw = Get(nw, 1);
		return nw;
	}
	
	void add(const T &x, const string &document, const K &k, bool &FG) {
		in.open(document, fstream::in | fstream::binary);
		if(!in) {
			in.open(document, fstream::out);
			Write_num(0, 1, 0), Write_num(0, 2, 0), Write_num(0, 3, 0);
		};
		in.close();
		in.open(document, fstream::in | fstream::out | fstream::binary);
		//if(document == "act_system.txt") printf("Get_sum = %d Get_num = %d\n", Get(0, 1), Get(0, 2));
		int pre = find_mn(k), nxt = find_mx(k);
		//cout << "pre = " << pre << "nxt = " << nxt << endl;
		if(pre != 0 && pre == nxt) {// Invalid
			puts("Yse_onho");
			FG = false;			
		} else {
			int sum, num;
			sum = Get(0, 1), num = Get(0, 2);
			++ sum, ++ num;
			Write_num(0, 1, sum);Write_num(0, 2, num);
			if(pre == 0 && nxt == 0) {
				Write_num(0, 3, num);
				
				Write_num(num, 1, 0), Write_num(num, 2, 0), Write_num(num, 3, num);
			} else if(pre == 0) {
				Write_num(0, 3, num);
				
				Write_num(num, 1, pre), Write_num(num, 2, nxt);
				int last = Get(nxt, 3);
				Write_num(num, 3, last);
				
				Write_num(nxt, 1, num);
				
			} else if(nxt == 0) {
				
				Write_num(num, 1, pre), Write_num(num, 2, nxt);
				int last = num;
				Write_num(num, 3, last);
				int pr = pre;
				while(pr != 0 && Get(pr, 3) == pre) {
					Write_num(pr, 3, last);
					pr = Get(pr, 1);
				}
				Write_num(pre, 2, num);
				
			} else {
				
				Write_num(num, 1, pre), Write_num(num, 2, nxt);
				int last = Get(nxt, 3);
				Write_num(num, 3, last);
				
				Write_num(nxt, 1, num);
				Write_num(pre, 2, num);
			}
			Write_K(num, k), Write_type(num, x);	
						
			int last = Get(num, 3);
			int siz = Get_size(last);
			if(siz > BLOCK_MAX) {
				int mid = Find_pre(last, siz / 2);	
				int nw = mid;
				while(nw != 0 && Get(nw, 3) == last) {
					Write_num(nw, 3, mid);
					nw = Get(nw, 1);
				}
			}
		}
		in.close();
		return;
	}
	
	void Merge(int last1, int last2) {
		int nw = last1;
		while(nw != 0 && Get(nw, 3) == last1) {
			Write_num(nw, 3, last2);
			nw = Get(nw, 1);
		}
		return;
	}
	
	void del(const string &document, const K &k, bool &FG) {
		in.open(document, fstream::in | fstream::binary);
		if(!in) { // Invalid
			FG = false;
		} else {
			in.close();
			in.open(document, fstream::in | fstream::out | fstream::binary);
			int pre = find_mn(k), nxt = find_mx(k); //puts("del_over");
			if(!(pre != 0 && pre == nxt)) { // Invalid
				FG = false;
			} else {
				int sum = Get(0, 1), num = Get(0, 2);			
				-- sum;
				Write_num(0, 1, sum);
				
				int nw = pre, last = Get(pre, 3);
				pre = Get(nw, 1), nxt = Get(nw, 2);
				
				if(pre == 0 && nxt == 0) {
					Write_num(0, 3, 0);
					last = 0;
				} else if(pre == 0) {
					Write_num(0, 3, nxt);
					Write_num(nxt, 1, 0);
					if(Get(nxt, 3) != last) last = 0;
				} else if(nxt == 0) {
					Write_num(pre, 2, 0);
					
					int now_last = pre;
					while(pre != 0 && Get(pre, 3) == nw) {
						Write_num(pre, 3, now_last);
						pre = Get(pre, 1);
					}
					last = now_last;
				} else {
					Write_num(pre, 2, nxt);
					Write_num(nxt, 1, pre);
					if(Get(nw, 3) == nw) {
						int now_last = pre;
						while(pre != 0 && Get(pre, 3) == nw) {
							Write_num(pre, 3, now_last);
							pre = Get(pre, 1);
						}
						last = now_last;
					} else if(Get(pre, 3) != Get(nw, 3)) last = Get(nxt, 3);
				}
				
				int siz = Get_size(last);
				if(siz < BLOCK_MIN) {
					int p_pre = Find_pre(last, siz);
					if(p_pre && Get_size(p_pre) + siz < BLOCK_MAX) Merge(p_pre, last);
					int n_nxt = Get(last, 2);
					if(n_nxt && Get_size(Get(n_nxt, 3)) + Get_size(last) < BLOCK_MAX) Merge(last, Get(n_nxt, 3));
				}
			}
			in.close();
			
		}
		return;
	}
	
	bool Find(const K &k, const string &document, T &id, bool &FG) {
		in.open(document, fstream::in | fstream::binary);
		bool ret = false;
		
		if(!in) { FG = false;
		} else {
			in.close();
			in.open(document, fstream::in | fstream::out | fstream::binary);
			
			int sum = Get(0, 1), num = Get(0, 2), st = Get(0, 3);
			int pre = find_mn(k), nxt = find_mx(k);
			
			if(pre != 0 && pre == nxt) {
				ret = true;
				Inseekg(pre, 4), in.seekg(sizeof(K), ios::cur);
				in.read(reinterpret_cast<char *>(&id), sizeof(T));
			} else ret = false;
			in.close();
		}
		
		return ret;
	}
	
	void modify(const K &k, const string &document, const T &x, bool &FG) {
		in.open(document, fstream::in | fstream::binary);
		if(!in) {
			FG = false;
		} else {
			in.close();
			in.open(document, fstream::in | fstream::out | fstream::binary);
			int pre = find_mn(k), nxt = find_mx(k);
			if(pre != 0 && pre == nxt) Write_type(pre, x);
			else FG = false;
			in.close();
		}
		return;
	}
	
	void display(const string &document, bool &FG) {
		in.open(document, fstream::in | fstream::binary);
		if(!in) {// Invalid;
		} else {
			in.close();
			in.open(document, fstream::in | fstream::out | fstream::binary);
			int st = Get(0, 3);
			T nw;
			while(st != 0) {
				Inseekg(st, 4);
				in.seekg(sizeof(K), ios::cur);
				in.read(reinterpret_cast<char *>(&nw), sizeof(T));
				cout << nw << endl;
				st = Get(st, 2);
			}
			in.close();
		}
		return;
	}
	
	void select(const K &k, const string &document, const T &x, bool &FG) {
		in.open(document, fstream::in | fstream::binary);
		if(!in) {
		} else {
			in.close();
			in.open(document, fstream::in | fstream::out | fstream::binary);
			bool fg = true; K nw_k; 
			int r = find_mn(k, 1), l;
			if(r == 0) fg = false;
			else {
				Inseekg(r, 4);
				in.read(reinterpret_cast<char *>(&nw_k), sizeof(K));
				if(nw_k.x != k.x) fg = false;
			}
			if(fg) {
				l = find_mx(k, 1);
				if(l == 0) fg = false;
				else {
					Inseekg(l, 4);
					in.read(reinterpret_cast<char *>(&nw_k), sizeof(K));
					if(nw_k.x != k.x) fg = false;
				}
			}
			if(fg) {
				T nw;
				while(true) {
					Inseekg(l, 4);
					in.seekg(sizeof(K), ios::cur);
					in.read(reinterpret_cast<char *>(&nw), sizeof(T));
					if(nw == x) cout << nw << endl;
					if(l == r) break;
					l = Get(l, 2);
				}
			}
			in.close();
		}
		
		return;
	}
	
	void select_all() {
		in.open("act_system.txt", fstream::in | fstream::out | fstream::binary);
		int st = Get(0, 3);
		T nw;
		while(st) {
			Inseekg(st, 4);
			in.seekg(sizeof(K), ios::cur);
			in.read(reinterpret_cast<char *>(&nw), sizeof(T));
			cout << nw << endl;
			st = Get(st, 2);
		}
		return;
	}
	
	void display_part(int tim, bool &FG) {
		in.open("finance.txt", fstream::in | fstream::out | fstream::binary);
		int num = Get(0, 2);
		if(tim > num) {
			FG = false;
		} else {
			T nw; double sum1 = 0, sum2 = 0;
			for(int i = num - tim + 1 ; i <= num ; ++ i) {
				Inseekg(i, 4);
				in.seekg(sizeof(K), ios::cur);
				in.read(reinterpret_cast<char *>(&nw), sizeof(T));
				if(nw.bg == 0) sum1 += nw.val;
				else sum2 += nw.val;
			}
			printf("+ %.2lf - %.2lf\n", sum1, sum2);
		}
		in.close();
		return;
	}
	
	void display_all(bool &FG) {
		in.open("finance.txt", fstream::in | fstream::out | fstream::binary);
		int num = Get(0, 2);
		in.close();
		display_part(num, FG);
		return;
	}
	
	
	void report() {
		in.open("finance.txt", fstream::in | fstream::out | fstream::binary);
		int num = Get(0, 2);
		T nw;
		for(int i = 1 ; i <= num ; ++ i) {
			Inseekg(i, 4);	
			in.seekg(sizeof(K), ios::cur);
			in.read(reinterpret_cast<char *>(&nw), sizeof(T));
			cout << nw << endl;
		}
		return;
	}
};

#endif
