
#include <iostream>
#include <string>
#include <cstdio>
#include "Scanner.h"

using namespace std;

int main() {
	Scanner sca;
	string s;
	cin >> s;
	for(int i = 0 ; i < s.length() ; ++ i) printf("s[%d] = %c\n", i, s[i]);
	if(s[4] == '|') puts("Yes");
	sca.Input(s);
	string token = sca.NextToken_3();
	cout << token; //人物|传记
	return 0;
}
