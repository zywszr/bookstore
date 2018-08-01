#ifndef BOOK_H
#define BOOK_H
#include <iomanip>
#include "String.h"
#include "Scanner.h"

class Book {
	friend class Book_store;
public:
	long long q;
	double money;
	String <25> isbn;
	String <50> name, author, keyword;
	
	Book() {
		q = 0, money = 0;
		return;
	}
	
	Book & operator = (const Book & x) {
		q = x.q, money = x.money;
		isbn = x.isbn, name = x.name, author = x.author, keyword = x.keyword;
		return (*this);
	}
	
	friend ostream & operator << (ostream & os, const Book &st) {
		os.setf(ios::fixed);
		os << st.isbn << '\t' << st.name << '\t' << st.author << '\t' << st.keyword << '\t' << fixed << setprecision(2) << st.money << '\t' << st.q << "本";
		return os;
	}
	
	friend bool operator == (const Book &x, const Book &y) {
		if(y.isbn != "" && x.isbn != y.isbn) return false;
		if(y.name != "" && x.name != y.name) return false;	
		if(y.author != "" && x.author != y.author) return false;
		return true;
	}
};

class Trade {
public:
	double val; bool bg; String <25> id; int q;
	friend ostream & operator << (ostream & os, const Trade &st) {
		os.setf(ios::fixed);
		if(st.bg == 0) {
			os << "销售书" << " " << st.id << " " << st.q << " 本收入 " << fixed << setprecision(2) << st.val;
		} else {
			os << "购买书" << " " << st.id << " " << st.q << " 本支出 " << fixed << setprecision(2) << st.val;
		}
		return os;
	}
};

class Book_store {

	#define bookkey KEY <String <25>, String <25>, 1>
	#define bookisbn String <25>
	
private:
	Data_base < KEY <String <25>, String <25>, 1>, Book> data_book;
	Data_base < KEY <String <50>, String <25>, 0>, Book> data_name;
	Data_base < KEY <String <50>, String <25>, 0>, Book> data_author;
	Data_base < KEY <String <50>, String <25>, 0>, Book> data_key;
	Data_base < KEY <int, int, 1>, Trade> data_finance;
	ifstream in;
	ofstream out;
	Scanner sca;
	int tradesum;
public:
	
	Book_store() {
	
		in.open("finance.txt");
		if(!in) {
			out.open("finance.txt");
			int x = 0;
			out.write(reinterpret_cast<char *>(&x), sizeof(int));
			out.write(reinterpret_cast<char *>(&x), sizeof(int));
			out.write(reinterpret_cast<char *>(&x), sizeof(int));
			out.close();
		} else in.close();
		in.open("book_system.txt");
		
		if(!in) {
			out.open("book_system.txt");
			int x = 0;
			out.write(reinterpret_cast<char *>(&x), sizeof(int));
			out.write(reinterpret_cast<char *>(&x), sizeof(int));
			out.write(reinterpret_cast<char *>(&x), sizeof(int));
			out.close();
			tradesum = 0;
		} else {
			in.read(reinterpret_cast<char *>(&tradesum), sizeof(int));
			in.close();
		}
		return;
	}
	
	void display(bool &FG) {
		data_book.display("book_system.txt", FG);
		return;
	}
	
	bool Find(const string &k, const string &document, Book &x, bool &FG) {
		return data_book.Find(bookkey(bookisbn(k)), document, x, FG);
	}
	
	void select(const Book &x, bool &FG) {
		if(x.keyword != "") {
			data_key.select(KEY <String <50>, String <25>, 0>(x.keyword, x.isbn), "book_key.txt", x, FG);
		} else if(x.isbn != "") {
			data_book.select(KEY <String <25>, String <25>, 1>(x.isbn), "book_system.txt", x, FG);
		} else if(x.name != "") {
			data_name.select(KEY <String <50>, String <25>, 0>(x.name, x.isbn), "book_name.txt", x, FG);
		} else if(x.author != "") {
			data_author.select(KEY <String <50>, String <25>, 0>(x.author, x.isbn), "book_author.txt", x, FG);
		}
		return;
	}
	
	void del(const Book &x, bool &FG) {
		data_book.del("book_system.txt", KEY <String <25>, String <25>, 1>(x.isbn), FG);
		if(x.name != "") data_name.del("book_name.txt", KEY <String <50>, String <25>, 0>(x.name, x.isbn), FG);
		if(x.author != "") data_author.del("book_author.txt", KEY <String <50>, String <25>, 0>(x.author, x.isbn), FG);
		sca.Input((string)(x.keyword));
		string token;
		while(true) {
			token = sca.NextToken_3();
			if(token == "") break;
			data_key.del("book_key.txt", KEY <String <50>, String <25>, 0>(String <50> (token), x.isbn), FG);
		}
		return;
	}
	
	void add(const Book &x, bool &FG) {
		data_book.add(x, "book_system.txt", KEY <String <25>, String <25>, 1>(x.isbn), FG);
		if(x.name != "") data_name.add(x, "book_name.txt", KEY <String <50>, String <25>, 0>(x.name, x.isbn), FG);
		if(x.author != "") data_author.add(x, "book_author.txt", KEY <String <50>, String <25>, 0>(x.author, x.isbn), FG);
		
		sca.Input((string)(x.keyword));
		string token;
		while(sca.HasMoreToken()) {
			token = sca.NextToken_3();
			if(token == "") continue;
			data_key.add(x, "book_key.txt", KEY <String <50>, String <25>, 0>(String <50> (token), x.isbn), FG);
		}
		return;
	}
	
	void modify(const Book &x, const Book &y, bool &FG) {
		del(x, FG);
		add(y, FG);
		return;
	}
	
	void modify1(const Book &x, bool &FG) {
		data_book.modify(KEY <String <25>, String <25>, 1>(x.isbn), "book_system.txt", x, FG);
		if(x.name != "") data_name.modify(KEY <String <50>, String <25>, 0>(x.name, x.isbn), "book_name.txt", x, FG);
		if(x.author != "") data_author.modify(KEY <String <50>, String <25>, 0>(x.author, x.isbn), "book_author.txt", x, FG);
		
		sca.Input(x.keyword);
		string token;
		while(true) {
			token = sca.NextToken_3();
			if(token == "") break;
			data_key.modify(KEY <String <50>, String <25>, 0>(String <50> (token), x.isbn), "book_key.txt", x, FG);
		}
		return;
	}
	
	void displayMoney(bool &FG) {
		data_finance.display_all(FG);
		return;	
	}
	
	void displayMoney(int tim, bool &FG) {
		if(tim < 0) { 
			puts("Invalid");
		} else if(tim == 0) return;
		else data_finance.display_part(tim, FG);
		return;
	}
	
	void addtrade(Trade &x, bool &FG) {
		++ tradesum;
		data_finance.add(x, "finance.txt", KEY <int, int, 1>(tradesum), FG);
		return;
	}
	
	void report_finance() {
		data_finance.report();
		return;	
	}
};

#endif
