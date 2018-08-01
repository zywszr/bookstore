
#include <cstdio>
#include <fstream>

using namespace std;

int main() {
	fstream out("test_.txt");
	
	int num = 1;
	out.seekp(ios::beg);
	out.write(reinterpret_cast<char *>(&num), sizeof(int));
	
	streamoff pos1 = out.tellg();
	streamoff pos2 = out.tellp();
	if(pos1 == pos2) puts("Yes");
	
	++ num;
	out.write(reinterpret_cast<char *>(&num), sizeof(int));
	
	pos1 = out.tellg();
	pos2 = out.tellp();
	if(pos1 == pos2) puts("Yes");
	
	//out.close();
	/**/
	//ifstream in("test_.txt");
	int cnt;
	pos1 = out.tellg();
	pos2 = out.tellp();
	if(pos1 == pos2) puts("Yes");
	out.seekg(pos1 - 2 * sizeof(int));
	out.read(reinterpret_cast<char *>(&cnt), sizeof(int));
	
	printf("cnt = %d\n", cnt);
	return 0;
}
