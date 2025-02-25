#include<iostream>
#include<string.h>
using namespace std;

void printRed(char* s){
	cout << "\033[31m" << s << "\033[0m";
}


int main(int argc,char** argv){
	string s;
	cin >> s;
	printRed(s);
}
