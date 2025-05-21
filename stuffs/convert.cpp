#include<iostream>
#include<stdint.h>
#include<string.h>
using namespace std;
void printRed(const string& s){
	cout << "\033[31m" << s << "\033[0m";
}
int main(int argc,char** argv){
	string s;
	cin >> s;
	printRed(s);
}
