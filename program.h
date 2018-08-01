#ifndef PROGRAM_H
#define PROGRAM_H

#include "Enum.h"
#include "Scanner.h"
#include "tool.h"
#include "book.h"
#include "user.h"
#include <string>

class Program {
	#define userkey  KEY < String <35>, String <35>, 1>
	#define userid String <35>
private:	
	Scanner sca, sca1;
	User now_user, new_user, blk_user;
	Book now_book, new_book, blk_book;
	Data_base <KEY <String <35>, String <35>, 1>, User> data_user;
	Data_base <KEY <String <35>, int, 0>, act> act_system;
	Book_store book_store;
	Trade tra;
	bool FG;
	ifstream in;
	int identity;
	char line[510];
public:
	Program() {
		identity = -1;
		data_user.Find(userkey(userid("root")), "user_system.txt", now_user, FG);
		return;
	}
	void getmessage(const char *s) {
		sca.Input(s);
		return;
	}
	void getmessage(string &s) {
		sca.Input(s);
		return;
	}
	void Get_user(int k) {
		if(k == 0) identity = 7, data_user.Find(userkey(userid("root")), "user_system.txt", now_user, FG);
		else now_user = blk_user;
		return;
	}
	void Get_message() {
		cin.getline(line, 510, '\n');
		getmessage(line);
		return;
	}
	void Get_identity() {
		while(identity == -1) {
			puts("请输入您的身份");
			puts("如果您是老板请输入 7 ， 如果您是员工请输入 3, 如果你是顾客请输入 1");
			while(true) {
				Get_message();
				string token = sca.NextToken();
				bool fg = true;
				if(token == "" || (!StringToInteger(token, identity))) fg = false;
				else {
					if(sca.HasMoreToken()) fg = false;
					else if(identity != 1 && identity != 3 && identity != 7) fg = false;	
				}
				if(fg) {
					puts("");
					break;
				} else {
					puts("您的输入不合法");
					puts("如果您是老板请输入 7 ， 如果您是员工请输入 3, 如果你是顾客请输入 1");
				}
			}
		}
		return;
	}
	int Get_number(int limit) {
		if(limit >= 3) puts("1：退出程序	2：登录账户	3：注册帐号");
		if(limit >= 7) puts("4：退出登录	5：修改账户密码	6：查询图书信息	7：购买图书");
		if(limit >= 12) {
			puts("8：创建账户	9：选定图书	10：修改图书信息");
			puts("11：进货图书	12：查看自己操作记录");
		}
		if(limit >= 18) {
			puts("13：批量操作	14：删除用户	15：查看账目情况");
			puts("16：查看财务报表	17：查看员工工作情况	18：查看日志记录");
		}
		int ret = 0;
		while(true) {
			Get_message();
			string token = sca.NextToken();
			bool fg = true;
			if(token == "" || (!StringToInteger(token, ret))) fg = false;
			else {
				if(sca.HasMoreToken()) fg = false;
				else {
					fg = false;
					for(int i = 1 ; i <= limit ; ++ i) if(ret == i) {
						fg = true;
						break;
					}
				}
			}
			if(fg) {
				puts("");
				return ret;
			} else {
				puts("您的输入不合法");
				if(limit >= 3) puts("1：退出程序	2：登录账户	3：注册帐号");
				if(limit >= 7) puts("4：退出登录	5：修改账户密码	6：查询图书信息	7：购买图书");
	   			if(limit >= 12) {
	   				puts("8：创建账户	9：选定图书	10：修改图书信息");
	   				puts("11：进货图书	12：查看自己操作记录");
	   			}
	   			if(limit >= 18) {
	   				puts("13：批量操作	14：删除用户	15：查看账目情况");
	   				puts("16：查看财务报表	17：查看员工工作情况	18：查看日志记录");
				}
			}
		}
	}
	bool execute(bool &Exit) {
		User _user = now_user;
		FG = true;
		string token;
		token = sca.NextToken();
		switch (stringtoope(token)) {
			case EXIT:
				if(sca.HasMoreToken()) FG = false;
				else Exit = true;
				break;
			case SU: 
				token = sca.NextToken();
				if(token == "") FG = false;
				else {
					User nxt_user;
					nxt_user.key = userkey(userid(token));
					if(!data_user.Find(nxt_user.key, "user_system.txt", nxt_user, FG)) FG = false;
					else {
						if(nxt_user.k > identity) FG = false;
						else {
							if(sca.HasMoreToken()) {
								token = sca.NextToken();
								if(String <35> (token) != nxt_user.passwd) FG = false;
								else {
									if(sca.HasMoreToken()) FG = false;
									else now_user = nxt_user; 
								}
							} else {
								if(nxt_user.k < now_user.k) now_user = nxt_user;
								else FG = false;
							}
						}
					}
				}
				break;
			case LOGOUT:
				if(now_user.k == 0) FG = false;
				else now_user = blk_user;
				break;
			case USERADD:
				new_user = blk_user;
				token = sca.NextToken();
				if(token == "") FG = false;
				else {
					if(data_user.Find(userkey(userid(token)), "user_system.txt", new_user, FG)) FG = false;
					else {
						new_user.id = token;
						token = sca.NextToken();
						if(token == "") FG = false;
						else {
							new_user.passwd = token;
							token = sca.NextToken();
							if(token == "") FG = false;
							else {
								if(!StringToInteger(token, new_user.k)) FG = false;
								else {
									if(new_user.k != 1 && new_user.k != 3 && new_user.k != 7) FG = false;
									else {
										if(new_user.k >= now_user.k) FG = false;
										else {
											token = sca.NextToken();
											if(token == "") FG = false;
											else {
												new_user.name = token;
												if(sca.HasMoreToken()) FG = false;
												else data_user.add(new_user, "user_system.txt", userkey(new_user.id), FG);
											}
										}
									}
								}
							}
						}
					}
				}
				break;
			case REGISTER:
				new_user = blk_user; new_user.k = 1;
				token = sca.NextToken();
				if(token == "") FG = false;
				else {
					if(data_user.Find(userkey(userid(token)), "user_system.txt", new_user, FG)) FG = false;
					else {
						new_user.id = token;
						token = sca.NextToken();
						if(token == "") FG = false;
						else {
							new_user.passwd = token;
							token = sca.NextToken();
							if(token == "") FG = false;
							else {
								new_user.name = token;
								if(sca.HasMoreToken()) FG = false;
								else data_user.add(new_user, "user_system.txt", new_user.id, FG);
							}
						}
					}
				}
				break;
			case DELETE:
				if(now_user.k < 7) FG = false;
				else {
					token = sca.NextToken();
					if(token == "") FG = false;
					else {
						if(sca.HasMoreToken()) FG = false;
						else data_user.del("user_system.txt", userkey(userid(token)), FG);
					}
				}
				break;
			case PASSWD:
				new_user = blk_user;
				token = sca.NextToken();
				if(token == "") FG = false;
				else {
					if(!data_user.Find(userkey(userid(token)), "user_system.txt", new_user, FG)) FG = false;
					else {
						if(now_user.id == "root") {
							token = sca.NextToken();
							if(token == "") FG = false;
							else {
								new_user.passwd = token;
								if(sca.HasMoreToken()) FG = false;
								else data_user.modify(new_user.id, "user_system.txt", new_user, FG);
							}
						} else {
							token = sca.NextToken();
							if(token == "" || userid(token) != new_user.passwd) FG = false;
							else {
								token = sca.NextToken();
								if(token == "") FG = false;
								else {
									new_user.passwd = token;
									if(sca.HasMoreToken()) FG = false;
									else data_user.modify(new_user.id, "user_system.txt", new_user, FG);
								}
							}
						}
					}
				}
				break;
			case SELECT:
				new_book = blk_book;
				token = sca.NextToken();
				if(token == "") FG = false;
				else {
					if(!book_store.Find(token, "book_system.txt", new_book, FG)) {
						new_book.isbn = token;
						if(sca.HasMoreToken()) FG = false;
						else book_store.add(new_book, FG), now_book = new_book;
					} else {
						if(sca.HasMoreToken()) FG = false;
						else now_book = new_book;
					}
				}
				break;
			case MODIFY:
				new_book = now_book;
				if(now_book.isbn == "")	FG = false;
				else {
					bool fg = true; 
					while(true) {
						token = sca.NextToken_1();
						if(token == "") break;
						string str = token;
						if(str == "-ISBN=") {
							token = sca.NextToken();
							if(token == "") {
								fg = false;
								break;
							} else new_book.isbn = token;
						} else if(str == "-name=") {
							token = sca.NextToken_2();
							if(token == "") {
								fg = false;
								break;
							} else {
								str = "";
								for(int i = 1 ; i < token.length() - 1 ; ++ i) str += token[i];
								new_book.name = str;
							}
						} else if(str == "-author=") {
							token = sca.NextToken_2();
							if(token == "") {
								fg = false;
								break;
							} else {
								str = "";
								for(int i = 1 ; i < token.length() - 1 ; ++ i) str += token[i];
								new_book.author = str;
							}
						} else if(str == "-keyword=") {
							token = sca.NextToken_2();
							if(token == "") {
								puts("NOfalse");
								fg = false;
								break;
							} else {
								str = "";
								for(int i = 1 ; i < token.length() - 1 ; ++ i) str += token[i];
								sca1.Input(str);
								str = "";
								while(sca1.HasMoreToken()) {
									token = sca1.NextToken_3();
									if(token != "") {
										if(str == "") str += token;
										else str += '|' + token;
									}
								}
								new_book.keyword = str;
							}
						} else if(str == "-price=") {
							token = sca.NextToken();
							if(token == "") {
								fg = false;
								break;
							} else {
								if(!StringToReal(token, new_book.money)) {
									fg = false;
									break;
								}
							}
						} else {
							fg = false;
							break;
						}
					}
					if(!fg) FG = false;
					else {
						book_store.del(now_book, FG);
						Book other_book;
						if(book_store.Find((string)(new_book.isbn), "book_system.txt", other_book, FG)) {
							FG = false;
							book_store.add(now_book, FG);
						} else book_store.add(new_book, FG), now_book = new_book;
					}
				}
				break;
			case IMPORT:
				int q; double price;
				if(now_book.isbn == "")	FG = false;
				else {
					token = sca.NextToken();
					if(token == "" || (!StringToInteger(token, q))) FG = false;
					else {
						token = sca.NextToken();
						if(token == "" || (!StringToReal(token, price))) FG = false;	
						else {
							if(sca.HasMoreToken()) FG = false;
							else {
								now_book.q += (long long)q, book_store.modify1(now_book, FG);	
								tra.bg = 1, tra.val = price, tra.id = now_book.isbn, tra.q = q;
								book_store.addtrade(tra, FG);
							}
						}
					}
				}
				break;
			case SHOW:
				if(now_user.k == 0) FG = false; 
				else {
					sca1 = sca;
					token = sca.NextToken();
					if(token == "") book_store.display(FG);
					else {
						if(token == "finance") {
							token = sca.NextToken();
							if(token == "") book_store.displayMoney(FG);
							else {
								int tim;
								if(!StringToInteger(token, tim)) FG = false;
								else {
									if(sca.HasMoreToken()) FG = false;
									else book_store.displayMoney(tim, FG);
								}
							}
						} else {
							Book new_book;
							bool fg = true; 
							while(true) {
								token = sca1.NextToken_1();
								if(token == "") break;
								string str = token;
								if(str == "-ISBN=") {
									token = sca1.NextToken();
									if(token == "") {
										fg = false;
										break;
									} else new_book.isbn = token;
								} else if(str == "-name=") {
									token = sca1.NextToken_2();
									if(token == "") {
										fg = false;
										break;
									} else {
										str = "";
										for(int i = 1 ; i < token.length() - 1 ; ++ i) str += token[i];
										new_book.name = str;
									}
								} else if(str == "-author=") {
									token = sca1.NextToken_2();
									if(token == "") {
										fg = false;
										break;
									} else {
										str = "";
										for(int i = 1 ; i < token.length() - 1 ; ++ i) str += token[i];
										new_book.author = str;
									}
								} else if(str == "-keyword=") {
									token = sca1.NextToken_2();
									if(token == "") {
										fg = false;
										break;
									} else {
										str = "";
										for(int i = 1 ; i < token.length() - 1 ; ++ i) str += token[i];
										Scanner sca2;
										sca2.Input(str);
										str = "";
										while(sca2.HasMoreToken()) {
											token = sca2.NextToken_3();
											if(token != "") {
												if(str == "") str += token;
												else {
													fg = false;
													break;
													str += '|' + token;
												}
											}
										}
										if(!fg) break;
										new_book.keyword = str;
									}
								} else {
									fg = false;
									break;
								}
							}
							if(!fg) FG = false;
							else book_store.select(new_book, FG);
						}
					}
				}
				break;
			case BUY:
				new_book = blk_book;
				token = sca.NextToken();
				if(token == "") FG = false;
				else {
					if(!book_store.Find(token, "book_system.txt", new_book, FG)) FG = false;
					else {
						token = sca.NextToken();
						int q;
						if(token == "" || (!StringToInteger(token, q))) FG = false;
						else {
							if(sca.HasMoreToken() || q > new_book.q) FG = false;
							else {
								new_book.q -= (long long)q, book_store.modify1(new_book, FG); 	
								tra.bg = 0, tra.val = (double)q * new_book.money;
								tra.id = new_book.isbn, tra.q = q; 
								book_store.addtrade(tra, FG);
							}
						}
					}
				}
				break;
			case REPORT:
				if(now_user.k < 3) FG = false;
				else {
					token = sca.NextToken();
					if(token == "") FG = false;
					else {
						if(token == "myself") {
							act nw;
							nw.id = _user.id, nw.action = "";
							act_system.select(KEY <String <35>, int, 0>(nw.id), "act_system.txt", nw, FG);
						//	printf("FG = %d\n", FG);
						} else if(token == "finance" || token == "employee") {
							if(now_user.k < 7) FG = false;
							else {
								if(token == "finance") {
									book_store.report_finance();	
								} else {
									act_system.select_all();
								}
							}
						} else FG = false;
					}		
				}
				break;
			case LOG:
				if(now_user.k < 7) FG = false;
				else {
					act_system.select_all();
					book_store.report_finance();	
				}
				break;
			default:
				FG = false;
				break;
		}
		if(FG) {
			if(_user.k > 0)	{
				act nw;
				nw.id = _user.id, nw.action = String <210> (sca.Get_str());
				int num;
				ifstream out("act_system.txt");
				out.read(reinterpret_cast<char *>(&num), sizeof(int));
				out.close();
				act_system.add(nw, "act_system.txt", KEY <String <35>, int, 0>(nw.id, num + 1), FG);
			}					
		}
		return FG;
	}	
	void Solve(int num, bool &Exit) {
		string now_str, token;
		switch (num) {
			case 1: 
				Exit = true;
				puts("程序已退出");
				break;
			case 2:
				puts("请在一行中按次序输入用户名id和密码，并用空格隔开, 如果您忘记密码，也可以尝试一下只输入用户id");
				Get_message();
				now_str = "su " + sca.Get_str();
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");
				break;
			case 3:
				puts("请在一行中按次序输入用户id，密码和名称，并用空格隔开");
				Get_message();
				now_str = "register " + sca.Get_str();
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");
				break;
			case 4:
				now_str = "logout";
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 5:
				puts("请在一行中按次序输入用户id，旧密码和新密码，并用空格隔开，如果您当前登录账户为root则不需要输入旧密码");
				Get_message();
				now_str = "passwd " + sca.Get_str();
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 6:
				puts("请在一行中输入书的ISBN号，名称，作者和关键字，例：‐ISBN=[ISBN] ‐name=[name] ‐author=[author] ‐keyword=[keyword]");
				puts("不要求输入顺序，各个参数可以省略， 并且[name] 和 [author] 被双引号包起来， [keyword]整体被双引号包起来,关键字之间 | 隔开");
				Get_message();
				now_str = "show " + sca.Get_str();
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 7:
				puts("请在一行中按次序输入图书ISBN号和购买数量，并用空格隔开");
				Get_message();
				now_str = "buy " + sca.Get_str();
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 8:
				puts("请在一行中按次序输入用户id、密码、权限（1/3/7）和名称，并用空格隔开");
				Get_message();
				now_str = "useradd " + sca.Get_str();
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 9:
				puts("请在一行中输入要选定图书的ISBN号");
				Get_message();
				now_str = "select " + sca.Get_str();
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 10:
				puts("请在一行中输入书的ISBN号，名称，作者，关键字和价格，例：‐ISBN=[ISBN] ‐name=[name] ‐author=[author] ‐keyword=[keyword] ‐price=[price]");
				puts("不要求输入顺序，各个参数可以省略， 并且[name] 和 [author] 被双引号包起来， [keyword]整体被双引号包起来,关键字之间 | 隔开");
				Get_message();
				now_str = "modify " + sca.Get_str();
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 11:
				puts("请在一行中按次序输入要进货图书的数量和总价格，并用空格隔开");
				Get_message();
				now_str = "import " + sca.Get_str();
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 12:
				getmessage("report myself");
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 13:
				puts("请输入含有操作命令的文档名称");
				Get_message();
				token = sca.NextToken();
				if(token == "") {//Invalid
				} else {
					if(sca.HasMoreToken()) {//Invalid
					} else {
						ifstream in(token);
						if(!in) puts("该文档不存在");	
						else {
							char lin[510];
							bool Exi;
							while(in.getline(lin, 510, '\n')) {
								if(lin == "EOF") break;
								getmessage(lin);
								if(!execute(Exi)) puts("Invalid");
								if(Exi) break;
							}
							in.close();
						}
					}
				}
				break;
			case 14:
				puts("请输入要删除的用户id");
				Get_message();
				now_str = "delete " + sca.Get_str();
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 15:
				puts("请输入n（要查看的近n次帐目记录的总和，如果要查看所有记录的总和，也可以不输入）");
				Get_message();
				now_str = "show finance " + sca.Get_str();
				getmessage(now_str);
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 16:
				getmessage("report finance");
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 17:
				getmessage("report employee");
				if(!execute(Exit)) puts("Invalid");;
				break;
			case 18:
				getmessage("log");
				if(!execute(Exit)) puts("Invalid");;
				break;
			default:
				break;
		}
		return;
	}
	void ask(bool &Exit) {
		if(identity == -1) Get_identity();
		puts("请输入对应的数字来选择您的操作：");
		int nw_number;
		if(now_user.k == 0) nw_number = Get_number(3);
		else if(now_user.k == 1) nw_number = Get_number(7);
		else if(now_user.k == 3) nw_number = Get_number(12);
		else nw_number = Get_number(18);
		Solve(nw_number, Exit);
		puts("");
		return;
	}
	
};

#endif
